#include <arpa/inet.h>
#include <fcntl.h>     
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>     
#include <stdlib.h>    
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h> 
#include <sys/types.h>
#include <unistd.h>

#define SIZE    128000

//foreground encryption
//*************************************
//begin main
int main(int argc, char *argv[]){
	//declare variables
	//socket and port information
    int sockfd, portno, n;
	//struct for our socket address, and server address
    struct sockaddr_in serv_addr;
	//hostent struct to the server
    struct hostent *server;
	//buffer for encrypted file
    char buffer[SIZE];
	//buffer for key file
    char keyBuffer[SIZE];
	//buffer for unencrypted file
    char buffer3[1];
	//variable to get the files
    int fp;
	//i for loops
    int i;
	//size of the key file
    int keyFileSize;
	//how much was recieved
    int retrieved;
	//how much data was sent
    int sent;
	//size of the encrypted file
    int inputFileSize;
    //first things first, verify the number of arguments that were recieved, if we have less than 4 we cannot run the program and exit out
    if (argc < 4){
		//print error to user
        printf("Usage: otp_enc plaintext key port\n");
		//exit program
        exit(1);
    }
	//if we make it past that, then mostly smooth sailing from there
	//we want to grab the port number specified in the argument array
    portno = atoi(argv[3]);   
    //we will open the file specified in the [1] position of our argument array in read Only
    fp = open(argv[1], O_RDONLY);
    //if fp returns null, it could not get the file, so we will error out
    if (fp < 0){
		//print error to user
        printf("Error: cannot open plaintext file %s\n", argv[1]);
		//exit the program
        exit(1);
    }
    //read the encrypted file into our buffer
    inputFileSize = read(fp, buffer, SIZE);
    //check the file for invalid or bad characters
    for (i = 0; i < inputFileSize - 1; i++){
		//if comparison to check value at the position in the buffer
        if ((int) buffer[i] > 90 || ((int) buffer[i] < 65 && (int) buffer[i] != 32)){
			//print error to user
            printf("otp_enc error: plaintext contains bad characters\n");
			//exit program
            exit(1);
        }
    }
    //close the file, we have it in buffer, and dont need it anymore
    close(fp);
    //same process for the key file
	//open the file listed in the argument[2] slot
    fp = open(argv[2], O_RDONLY);
    //if fp is null, we are unable to open the file, and will error out
    if (fp < 0){
		//print error to user
        printf("Error: cannot open key file %s\n", argv[2]);
		//exit the program
        exit(1);
    }
	//get the contents of the key file, and place it into the keybuffer
    keyFileSize = read(fp, keyBuffer, SIZE);
    //validation of the keyfile
    for (i = 0; i < keyFileSize - 1; i++){
		//if comparison to check value at the position in the buffer
        if ((int) keyBuffer[i] > 90 || ((int) keyBuffer[i] < 65 && (int) keyBuffer[i] != 32)){
			//print error to user
            printf("otp_enc error: key contains bad characters\n");
			//exit the program
            exit(1);
        }
    }
	//close the key file we grabbed, it is no longer needed
    close(fp);
    //key file has to be as long as the input file, so we will compare them, if its not, we will give an error to the user
    if (keyFileSize < inputFileSize){
		//print error
        printf("Error: key '%s' is too short\n", argv[2]);
    }
    //begin socket interaction
	//check af_inet and sock_stream, if return has problem, will keep null
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
	//if we still have a null, we will error out
    if (sockfd < 0)
    {
		//print error to user
        printf("Error: could not contact otp_enc_d on port %d\n", portno);
		//exit program
        exit(2);
    }
    //we want to clean up the ip address memory space
    memset(&serv_addr, '\0', sizeof(serv_addr));

	//set server to localhost's name
    server = gethostbyname("localhost");
	//if server is equivalent to null, we have an error
    if (server == NULL){
		//print error to user
        printf("Error: could not connect to otp_enc_d\n");
		//exit the program
        exit(2);
    }    
	//ipv4 socket structure
    serv_addr.sin_family = AF_INET;
    //bytecopy server address informarion
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
	//htons the port no to the sin port	
    serv_addr.sin_port = htons(portno);
	//if our bcopy ends up null, we will need to error out
    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
		//print error to user
        printf("Error: could not connect to otp_enc_d on port %d\n", portno);
		//exit the program
        exit(2);
    }
    //write the input file to our sockfd
    sent = write(sockfd, buffer, inputFileSize - 1);
	//if sent is null, we will error out, as it was unable to send
    if (sent < inputFileSize - 1)
    {
		//print the error to the user
        printf("Error: could not send plaintext to otp_enc_d on port %d\n", portno);
		//exit the program
        exit(2);
    }
	//*********************************************************************************************
    memset(buffer3, 0, 1);
    // get acknowledgement from server
    retrieved = read(sockfd, buffer3, 1);
	//if the balue retrieved is null or negative, we have an error
    if (retrieved < 0){
		//print error to user
       printf("Error receiving acknowledgement from otp_enc_d\n");
	   //exit the program
       exit(2);
    }
    //write out key
    sent = write(sockfd, keyBuffer, keyFileSize - 1);
	//if sent is null or negative, we had an error writing, and will error out
    if (sent < keyFileSize - 1){
		//print error to user
        printf("Error: could not send key to otp_enc_d on port %d\n", portno);
		//exit the program
        exit(2);
    }
    //clear up the encrypted file buffer
    memset(buffer, 0, SIZE);
	//do while to continue looping retrieved file until we have nothing left to grab
    do{
        //text will come back as encrypted
        retrieved = read(sockfd, buffer, inputFileSize - 1);
    }
    while (retrieved > 0);
	//compare retrieved, if null or negative, there is an error, and we need to exit
    if (retrieved < 0){
		//print error to user
       printf("Error receiving ciphertext from otp_enc_d\n");
	   //exit the program
       exit(2);
    }
    //print contents of buffer to the console window
    for (i = 0; i < inputFileSize - 1; i++){
		//print char at buffer[i] position
        printf("%c", buffer[i]);
    }
    printf("\n");
    //close the socket
    close(sockfd);
    return 0;
}
//end method main
//************************************************