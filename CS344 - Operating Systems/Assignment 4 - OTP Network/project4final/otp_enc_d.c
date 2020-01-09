#include <fcntl.h>     
#include <netinet/in.h>
#include <stdio.h>     
#include <stdlib.h>    
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>

#define SIZE    128000

//background daemon for encryption
//************************************************
//begin main
int main(int argc, char *argv[]){
    //initiate variables
	//socket and port information
    int sockfd, newsockfd, portno;
	//socklen_t variable
    socklen_t clilen;
	//struct for our socket address, server address, and our cli address
    struct sockaddr_in serv_addr, cli_addr;
	//int n for loops
    int n;
	//buffer for encrypted file
    char buffer[SIZE];
	//buffer for key file
    char keyBuffer[SIZE];
	//buffer for unencrypted file
    char buffer3[SIZE];
	//int i for loop
    int i;
	//size of the key file
    int keyFileSize;
	//size of inputfile
    int inputFileSize;
	//process id for fork
    int pid;
	//sent for checking if sent
    int sent;
    //check the number of arguments that were provided, if less than 2, exit the program 
    if (argc < 2){
		//print error to user
        printf("Usage: otp_enc_d port\n");
		//exit program
        exit(1);
    }
	//assign item in position argv[1] to be our port number
    portno = atoi(argv[1]);
    //create socket from port number, and check if it works or not, if not, error out
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		//print error to user
        printf("Error: opt_enc_d could not create socket\n");
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
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
		//print error to user
        printf("Error: otp_enc_d unable to bind socket to port %d\n", portno);
		//exit process
        exit(2);
    }
    //listen for connections
	//if listen equals -1, we have an error
    if (listen(sockfd, 5) == -1){
		//print error to user
        printf("Error: otp_enc_d unable to listen on port %d\n", portno);
		//exit program
        exit(2);
    }
	//set client length to size of client address
    clilen = sizeof(cli_addr);
	//we want to open all connections, fork, and loop our program until we finish
    while (1){
		//set new socket for client
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
		//if we recieve a null from our accept, there is a problem
        if (newsockfd < 0){
			//print error to user
            printf("Error: opt_enc_d unable to accept connection\n");
            continue;
        }
        //begin fork, using pid
        pid = fork();
		//if our pid is null, we will have an error
        if (pid < 0){
			//print error to user
            perror("opt_enc_c: error on fork\n");
        }
        //child process
		//if our pid is equal to zero, we are good to go
        if (pid == 0){
            //clean up our buffer
            memset(buffer, 0, SIZE);	
            //get length of our input file, as well as the contents
            inputFileSize  = read(newsockfd, buffer, SIZE);
			//if our file size ends up null, we have an error
            if (inputFileSize  < 0){
				//print error to user
                printf("Error: otp_end_d could not read plaintext on port %d\n", portno);
				//exit the program
                exit(2);
            }
            //send an acknowledgement to the client
            sent = write(newsockfd, "!", 1);
			//if sent is null or less than 1, we have a connection error
            if (sent < 0){
				//print error
                printf("otp_enc_d error sending acknowledgement to client\n");
				//exit program
                exit(2);
            }
            //clean up our buffer
            memset(keyBuffer, 0, SIZE);
            //get size of the key, and the contents of the file
            keyFileSize = read(newsockfd, keyBuffer, SIZE);
			//if we have a null, there is an issue reading the file
            if (keyFileSize < 0){
				//print the error
                printf("Error: otp_end_d could not read key on port %d\n", portno);
				//exit the program
                exit(2);
            }
            //check the encrypted file for invalid or bad characters
            for (i = 0; i < inputFileSize ; i++){
				//if comparison to check value at the position in the buffer
                if ((int) buffer[i] > 90 || ((int) buffer[i] < 65 && (int) buffer[i] != 32)){
					//error telling user that invalid characters were found
                    printf("otp_enc_d error: plaintext contains bad characters\n");
					//exit process
                    exit(1);
                }
            }
            //check the key file for invalid or bad characters
            for (i = 0; i < keyFileSize; i++){
				//if comparison to check value at the position in the buffer
                if ((int) keyBuffer[i] > 90 || ((int) keyBuffer[i] < 65 && (int) keyBuffer[i] != 32)){
					//error telling user that invalid characters were found
                    printf("otp_enc_d error: key contains bad characters\n");
					//exit the process
                    exit(1);
                }
            }
			//compare key file with input file, the key should be as long if not longer than the input file			
            if (keyFileSize < inputFileSize ){ 
				//error out if key is shorter, print error message to user
                printf("otp_enc_d error: key is too short\n");
				//exit process
                exit(1);
            }

            //encryption
            for (i = 0; i < inputFileSize ; i++){
                //change spaces to at symbols
				//do it for buffer
                if (buffer[i] == ' '){
                    buffer[i] = '@';
                }
				//do it for key
                if (keyBuffer[i] == ' '){
                    keyBuffer[i] = '@';
                }
                 //typecast for easier manipulation using ASCII
                int inputChar = (int) buffer[i];
                int keyChar = (int) keyBuffer[i];
                //we can change the ASCII range to help
                inputChar = inputChar - 64;
                keyChar = keyChar - 64;
				//get sum of input and key, then mod by 27 as the program instructions said
                int cipherText = (inputChar + keyChar) % 27;

                //we add 64 to make all characters appear as capital letters
                cipherText = cipherText + 64;

                //we are done with manipulation, so we will revert the variables back to characters
                buffer3[i] = (char) cipherText + 0;
				
                //change the at symbols back to spaces 
                if (buffer3[i] == '@'){
                    buffer3[i] = ' ';
                }
            }

            //now we want to write the encrypted text to the client
            sent = write(newsockfd, buffer3, inputFileSize );
			//check that sent is less than inpur file size, otherwise we have an error
            if (sent < inputFileSize ){
				//display error to user
                printf("otp_enc_d error writing to socket\n");
				//exit the program
                exit(2);
            }

			//cleanup time
            //clean up the sockets we had created
			
            close(newsockfd);
            close(sockfd);
			
			//exit the process
            exit(0);
        }
		//if we recieve an issue, we will close the new socket
        else close(newsockfd);
    } 

    return 0;
}
//end method main
//************************************************