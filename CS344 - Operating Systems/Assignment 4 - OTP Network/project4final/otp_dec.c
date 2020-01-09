//grab all of our includes
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
//establish large int for a buffer
#define SIZE    16000

//foreground decryption
//
//
//************************************************
//begin main
int main(int argc, char *argv[]){
	//declare variables
	//socket and port numbers
    int sockfd, portno, n;
	//struct for socket address and the server address
    struct sockaddr_in serv_addr;
	//host server pointer
    struct hostent *server;
	//creating a buffer to size variable, size variable is declared to be 16000
    char buffer[SIZE];
	//creating a key buffer the size of our size variable
    char keyBuffer[SIZE];
	//third buffer to contain compatason
    char buffer3[1];
	//***************************
    int fp;
	//int i for loop
    int i;
	//keyfilesize records size of the key file
    int keyFileSize;
	//records the size of the encrypted file
    int encryptFileSize;
	//packets recieved
    int retrieved;
	//packets sent
    int sent;

    //check the number of arguments provided
    if (argc < 4){
		//if arguments less than 4, we want to exit, 
        printf("Usage: otp_dec ciphertext key port\n");
		//as we want the otp_dec, the ciphertext, the key, and the port
        exit(1);
		//exit because invalid arguments
    }
	//grab port specified in the argument slot 3
    portno = atoi(argv[3]);
    
    //we will grab the encrypted file
    fp = open(argv[1], O_RDONLY);
	//if fp is still null, we want to exit, as we cannot do anything with it
    if (fp < 0){
		//display error that we could not open the file, and give file name
        printf("Error: cannot open ciphertext file %s\n", argv[1]);
        //exit to be readt for user to re-prompt
		exit(1);
    }

    //we will get the contents and the length of the file 
    encryptFileSize = read(fp, buffer, SIZE);

    //we want to check what was input for invalid/bad characters
    for (i = 0; i < encryptFileSize - 1; i++){
		//***************************************************************************************
        if ((int) buffer[i] > 90 || ((int) buffer[i] < 65 && (int) buffer[i] != 32)){
			//print error message for the user saying that the ciphertext had invalid/bad characters
            printf("otp_dec error: ciphertext contains bad characters\n");
            //exit to allow user to retry
			exit(1);
        }
    }

	//we will close the file, as we now have it in out buffer
    close(fp);

    //we will open our key file
    fp = open(argv[2], O_RDONLY);

	//file opening validation, if null cant open
    if (fp < 0){
		//prompt user with the error, saying that the provided file was unable to be opened
        printf("Error: cannot open key file %s\n", argv[2]);
		//exit for user to retry
        exit(1);
    }

    //we want to get the contents and the length of the key file, so we load it into our buffer
    keyFileSize = read(fp, keyBuffer, SIZE);

    //cipher input validation, check for bad or invalid characters 
    for (i = 0; i < keyFileSize - 1; i++){
		//*****************************************************************************
        if ((int) keyBuffer[i] > 90 || ((int) keyBuffer[i] < 65 && (int) keyBuffer[i] != 32)){
			//Display error to user
            printf("otp_dec error: key contains bad characters\n");
            //exit the program
			exit(1);
        }
    }
	//close the provided file, it is loaded into buffer now, and we no longer need the connection
    close(fp);

    //the key file that we make must be at least as long as input file 
    if (keyFileSize < encryptFileSize){
		//print error for user to show that input file is longer than the key
        printf("Error: key '%s' is too short\n", argv[2]);
    }

    //start our socket 
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
	//check if socket is null
    if (sockfd < 0){
		//socket was unable to be retrieved, report to the user including the port number that was used
        printf("Error: could not contact otp_dec_d on port %d\n", portno);
        //exit for user to retry
		exit(2);
    }
	//we want to clean up the ip address memory space
    memset(&serv_addr, '\0', sizeof(serv_addr));
	//we want to get the local host, and set it to be our server
    server = gethostbyname("localhost");
	//if server == null, we were unable to get the host name for localhost, therefore we will error out
    if (server == NULL){
		//display error to user
        printf("Error: could not connect to otp_dec_d\n");
        //exit out of the program for the user to retry
		exit(2);
    }    
	//ipv4 socket structure
    serv_addr.sin_family = AF_INET;
	//bytecopy server address informarion
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);         
    //htons the port no to the sin port
	serv_addr.sin_port = htons(portno);

	//if null, we were unable to connect, and want to tell the user 
    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
		//print the error
        printf("Error: could not connect to otp_dec_d on port %d\n", portno);
        //exit, allowing the user to retry
		exit(2);
    }

    
    //write the file for decryption 
    sent = write(sockfd, buffer, encryptFileSize - 1);
    //if the data sent is larger than the file's size, we have a problem
	if (sent < encryptFileSize - 1){
		//print error for user
        printf("Error: could not send ciphertext to otp_dec_d on port %d\n", portno);
        //exit the program for the user to retry
		exit(2);
    }
	//cleaning out buffer 3
    memset(buffer3, 0, 1);
    
    //get an acknowledgement from the server
    retrieved = read(sockfd, buffer3, 1);
    //if retrieved is null, we have a problem
	if (retrieved < 0){
		//print error for the user
       printf("Error receiving acknowledgement from otp_dec_d\n");
       //exit the program
	   exit(2);
    }

    //write the key for decryption 
    sent = write(sockfd, keyBuffer, keyFileSize - 1);
    //if the amount sent is larger than the actual file, we have a problem
	if (sent < keyFileSize - 1){
		//print error to the user
        printf("Error: could not send key to otp_dec_d on port %d\n", portno);
        //exit the program
		exit(2);
    }

    //clear our buffer 
    memset(buffer, 0, SIZE);
	//do while to loop through and recieve all the information 
    do{
        //read the contents 
        retrieved = read(sockfd, buffer, encryptFileSize - 1);
    }
    while (retrieved > 0);
	//do that while we have retrieved information from the loop
	//if we retrieved a null, we will error out
    if (retrieved < 0){
		//print error for user
       printf("Error receiving ciphertext from otp_dec_d\n");
       //exit for user to retry
	   exit(2);
    }

    //print it to the console 
    for (i = 0; i < encryptFileSize - 1; i++){
		//print the character inside of the buffer
        printf("%c", buffer[i]);
    }
	
    printf("\n");
	//close the socket
    close(sockfd);
    return 0;
}
//end method main
//************************************************