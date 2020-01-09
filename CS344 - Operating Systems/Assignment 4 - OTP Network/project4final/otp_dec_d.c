//imports
#include <fcntl.h>     
#include <netinet/in.h>
#include <stdio.h>     
#include <stdlib.h>   
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>
//declare size variable appropriate for buffer
#define SIZE    16000

//background daemon for decryption
//*************************************
//begin main
int main(int argc, char *argv[]){
	//declare our variables
    //socket and port information
	int sockfd, newsockfd, portno;
	//socklen_t variable
    socklen_t clilen;
	//struct for our socket address, server address, and our cli address
    struct sockaddr_in serv_addr, cli_addr;
	//int n for loops
    int n;
	//normal buffer for our data to be loaded into
    char buffer[SIZE];
	//key buffer for comparison
    char keyBuffer[SIZE];
	//buffer 3 for final product
    char buffer3[SIZE];
	//int i for loops
    int i;
	//key file size to be declared when we read the key file
    int keyFileSize;
	//sent variable for comparison when we are sending the file
    int sent;
	//process id
    int pid;
	//size of encrypted file
    int encryptFileSize;
    //we want to check the number of arguments 
    if (argc < 2){
		//if less than 2, we will error outp
        printf("Usage: otp_dec_d port\n");
		//exit
        exit(1);
    }
	//take the given port number in the arguments, and assign it to be our port
    portno = atoi(argv[1]);  
    //starting the  socket 
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("Error: otp_dec_d could not create socket\n");
        exit(1);
    }
	//we want to clean up the ip address memory space
    memset(&serv_addr, '\0', sizeof(serv_addr));
	//ipv4 socket structure
    serv_addr.sin_family = AF_INET;
	//we dont need to bind the socket to a specific ip, so we will grab any
    serv_addr.sin_addr.s_addr = INADDR_ANY;
	//converting to network byte
    serv_addr.sin_port = htons(portno);
    //binding the socket 
	//if result is null or negative, we will error out, as we are unable to continue
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
		//print error to the user
        printf("Error: otp_dec_d unable to bind socket to port %d\n", portno);
		//exit the program for the user to retry
        exit(2);
    }
	//if the returned value for our listen is equivalant to -1, we have a problem where we cannot listen to that port
    if (listen(sockfd, 5) == -1){
		//print error to user
        printf("Error: otp_dec_d unable to listen on port %d\n", portno);
        //exit the program for the user to retry
		exit(2);
    }
	//client length is the size of the client_address
    clilen = sizeof(cli_addr);
    //we want to loop for all of the connections until we are finished 
    while (1){
		//constructing a new socket
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
		//if null, we cant accept, will just loop back
        if (newsockfd < 0){
			//we will print an error to the user, and continue the program
            printf("Error: otp_dec_d unable to accept connection\n");
            continue;
        }
        //fork 
        pid = fork();
		//if pid is null we will tell the user theres an error, but continue
        if (pid < 0){
			//prompt user with problem
            perror("otp_dec_c: error on fork\n");
        }
        //child process
		//if process id is equivalant to zero, we will begin reading the encrypted file
        if (pid == 0){
			//set aside memory to store content in our buffer
            memset(buffer, 0, SIZE);

            //begin reading the encrypted file, and place into our buffer
            encryptFileSize = read(newsockfd, buffer, SIZE);
			//if filesize is negative or null we will have an error
            if (encryptFileSize < 0){
				//print the error to the user
                printf("Error: otp_end_d could not read ciphertext on port %d\n", portno);
				//exit to allow the user to retry
                exit(2);
            }   
            //send an acknowledgement to the client
			//update sent value to make a comparison
            sent = write(newsockfd, "!", 1);
			//if sent is null, we failed at comparing, and need to error out
            if (sent < 0){
				//print error to user
                printf("otp_enc_d error to client\n");
				//exit out of the program to allow user to retry
                exit(2);
            }
            //clear our buffer 
            memset(keyBuffer, 0, SIZE);
            //read our key file into buffer 
            keyFileSize = read(newsockfd, keyBuffer, SIZE);
			//if keyfilesize is null, we have an issue, and will error out 
            if (keyFileSize < 0){
				//print error to user
                printf("Error: otp_dec_d could not read key on port %d\n", portno);
				//exit the program
                exit(2);
            }
            //checking the encrypted file for invalid/bad characters
			//loop to go through the whole file
            for (i = 0; i < encryptFileSize; i++){
				//if comparison to check value at the position in the buffer
                if ((int) buffer[i] > 90 || ((int) buffer[i] < 65 && (int) buffer[i] != 32)){
					//print error to user
                    printf("otp_dec_d error: ciphertext contains bad characters\n");
					//exit out of the program
                    exit(1);
                }
            }
            //checking the key for invalid/bad characters 
            for (i = 0; i < keyFileSize; i++){
				//if comparison to check value at the position in the keybuffer
                if ((int) keyBuffer[i] > 90 || ((int) keyBuffer[i] < 65 && (int) keyBuffer[i] != 32)){
					//print error to the user
                    printf("otp_dec_d error: key contains bad characters\n");
					//exit the program
                    exit(1);
                }
            }
            //the key file we have has to be at least as long as our encrypted file, 
			//if it is not, we will error out
			//compare both keyfilesize and the encryptfilesize
            if (keyFileSize < encryptFileSize){ 
				//print the error to the user
                printf("otp_dec_d error: key is too short\n");
				//exit the program
                exit(1);
            }
            //decrypt the file 
            for (i = 0; i < encryptFileSize; i++){
                // change spaces to at symbol
				//do it for buffer
                if (buffer[i] == ' '){
                    buffer[i] = '@';
                }
				//do it for keybuffer
                if (keyBuffer[i] == ' '){
                    keyBuffer[i] = '@';
                }
                //typecast for easier manipulation using ASCII
                int inputChar = (int) buffer[i];
                int keyChar = (int) keyBuffer[i];
                //we can change the ASCII range to help
                inputChar = inputChar - 64;
                keyChar = keyChar - 64;
                //update for program specifications, and use key to begin deciphering
                int cleanText = inputChar - keyChar;		
				//fix up negative numbers 
                if (cleanText < 0){
					//incriment by 27 to get values out of negative range to avoid errors
                    cleanText = cleanText + 27;
                }
                //now that we have our letters, we want to make them capital, so we will just add 64 to them
                cleanText = cleanText + 64;
                //change the type of the variable back
                buffer3[i] = (char) cleanText + 0;
                //change the at symbols back to spaces after encryption
				if (buffer3[i] == '@'){
                    buffer3[i] = ' ';
                }
				//and decryption is done
            }
            //send contents of buffer3 (our decrypted file)
            sent = write(newsockfd, buffer3, encryptFileSize);
			//if we recieve a null, connection was interrupted, and we want to error out
            if (sent < encryptFileSize){
				//print error for user
                printf("otp_dec_d error writing to socket\n");
				//exit the program
                exit(2);
            }
			//close the new socket
            close(newsockfd);
			//close the old socket
            close(sockfd);
			//exit with value zero
            exit(0);
        }
		//catch anything that has a problem, and close the new socket
        else close(newsockfd);
    } 
    return 0;
}
//end main
//*************************************