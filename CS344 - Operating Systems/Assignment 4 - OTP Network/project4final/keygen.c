#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Keygen
//
//

//initiate randint
int randInt(int min, int max);

//************************************************
//begin main
int main(int argc, char *argv[]){
	//declare variables, and grab time_t
    char randLetter;
    int i;
    int length;
    time_t sysClock;

    //check if we were given arguments
    if (argc < 2){
        printf("arguments recieved\nusage: keygen keyLength\n");
		//exit if there are less than 2 arguments
        exit(1);
    }
	//get the length of the item that was specified for our key file
    sscanf(argv[1], "%d", &length);

	//exit if invalid length
    if (length < 1){
		//if there is no contents of the file, print an error
        printf("keygen error invalid keyLength\n");
		//exit program
        exit(1);
    }
	
	//seed our random number generator with the time
    srand((unsigned) time(&sysClock));
	//------
	//get our random letters
    for (i = 0; i < length; i++){
        //generate random letter and random int
        randLetter = (char) randInt(64, 90);

        //special case
        if (randLetter == '@'){
			//if we find the @ symbol, it translates to space
           randLetter = ' ';
        }
		//print contents of randletter
        printf("%c", randLetter);
    }

    printf("\n");
	//return
    return 0;
}
//end method main
//*************************************************


//*******************************************************
//randInt
//accept min and max inputs
int randInt(int min, int max){   
	//generate random number within range given by method calling this
    return rand() % (max - min + 1) + min;
}
//*****************************************************