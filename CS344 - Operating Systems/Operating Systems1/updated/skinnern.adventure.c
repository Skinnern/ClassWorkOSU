#include <stdio.h>
#include <stdlib.h>
#include <string.h>         
#include <unistd.h>         // gets PID to name dir
#include <fcntl.h>          // creating dir
#include <time.h>           // seeding srand
// DEFINING SOME MACROS
#define NumRooms 6
#define BUFFER_SIZE 512


//gcc {filename} -o {exe to create}
// ./{exe to create}

//construct the structure for rooms
struct ConstrRoom
{
	//room name 20 char max
    char name[20];
	//2d array to list room, and connecting areas
    char connectingRooms[NumRooms][20];
	//number of connections given room has
    int connectionTotal;
    char type[20];
}; //end inital struct ConstrRoom
//**************************************************************************************************





//**************************************************************************************************
//begin method printRoom
//print current room, and possible rooms for user to enter
void printRoom(struct ConstrRoom* r){
    //print the current location the user is in
    printf("CURRENT LOCATION: %s\n", r->name);
	//print the rooms that are adjacent to the current position, get these rooms from files
    printf("POSSIBLE CONNECTIONS: "); 
    int i;    
	//iterate through file to show all possible connections
    for (i=0; i < r->connectionTotal; i++){
        if(i+1 < r->connectionTotal)        
            printf("%s, ",r->connectingRooms[i]);
        else if (i+1 == r->connectionTotal)
            printf("%s.\n",r->connectingRooms[i]);
    }
	//give user location to input values
    printf("WHERE TO?>");         
}
//end method printRoom
//**************************************************************************************************





//**************************************************************************************************
//begin method readRoomFile
struct ConstrRoom* readRoomFile(char* inputFile){

    FILE* f;
    f = fopen(inputFile, "r");
    char line[BUFFER_SIZE];
    
    struct ConstrRoom *r = malloc(sizeof(struct ConstrRoom));
    r->connectionTotal = 0;
    
    char* token;
    
    // parses the file, line by line and builds a ConstrRoom struct
    if (f) {
        while(fgets(line,BUFFER_SIZE,f)) {
            // search line for ' ' delimiter
            token = strtok(line, " ");
            
            while (token != NULL ){
                
                if (strcmp("ROOM", token) == 0){
                    token = strtok(NULL, " ");
                    // get room name
                    if(strcmp("NAME:", token) == 0){
                        token = strtok(NULL, "\n");
                        strcpy(r->name, token);
                        break;
                    }
                    // get room type
                    if(strcmp("TYPE:", token) == 0){
                        token = strtok(NULL, "\n");
                        strcpy(r->type, token);
                        break;
                    }
                }
                // get connections
                if (strcmp("CONNECTION", token) == 0){
                    token = strtok(NULL, " ");
                    // token is an int now
                    int i = atoi(token);
                    i--; // set up index
                    token = strtok(NULL, "\n");
                    strcpy(r->connectingRooms[i], token);
                    r->connectionTotal++;
                    break;                    
                }
            }
        }
    fclose(f);
    }
    return r;
}
//end method readRoomFile
//**************************************************************************************************





//**************************************************************************************************
//begin method findStart
//find the starting room by reading type from file
struct ConstrRoom* findStart(struct ConstrRoom* r) {
    int i;
	//loop to iterate through and read each room generated
    for(i=0; i<7; i++) {
		//scan file to find if the room's type is equal to START_ROOM
        if(strcmp(r[i].type, "START_ROOM") == 0) {
			//return where the starting room is
            return &r[i];
        }
    }
}
//end method findStart
//**************************************************************************************************











//**************************************************************************************************
//begin method main
//it took me at least a day to remember that main could only call on methods that were above it,
//so a good portion of my code has been modified from just being written inside the main
int main(int argc, char** argv) {

    // seed rand with current time
    srand(time(NULL));
    
	
	/*
    // creates the room structures from memory and saves them in structs
    struct ConstrRoom *myHouse = chdir(skinnern.rooms);
    
    // builds files from the structs and places them in a new directory
    createFiles(myHouse);
	*/
	//char dirname[128];
    
    // builds the name of directory
    //sprintf(dirname, "skinnern.rooms"); 
	
	//struct ConstrRoom *myHouse = chdir(dirname);
	
	struct ConstrRoom *myHouse;
	
	
	
	
	
    // search for the starting room and copy the name of the room
    struct ConstrRoom *startRoom = findStart(myHouse);
    char startName[20];
    strcpy(startName, startRoom->name);

    // room pointers that are used in game loop   
    struct ConstrRoom *current;
    struct ConstrRoom *nameValidation;

    // variables to count steps and the path from start to finish
    int steps = 0;
    char path[BUFFER_SIZE];

    // set starting location
    current = readRoomFile(startName);
    
    // main game loop
    do {
        printRoom(current);
        
        // get user input and clear input stream
        char nextLoc[20];
        scanf ("%s", nextLoc);
        while ( getchar() != '\n' );
        
        nameValidation = readRoomFile(nextLoc);
        
        // user enters an invalid name 
        if(strcmp(nameValidation->name, nextLoc) != 0){
            printf("\nHUH? I DON’T UNDERSTAND THAT ROOM. TRY AGAIN.\n\n");
        }
        
        // user enters name of the current room
        else if(strcmp(current->name, nextLoc) == 0){
            printf("\n");
        }
        
        // user has entered a valid input
        else {
            // builds path taken string and increases steps taken
            strcat(path, current->name);
            strcat(path, "\n");
            steps++;
            
            // clean up memory
            free(current);
            
            // move to the next location
            current = readRoomFile(nextLoc);
            printf("\n");
        }
        
        // clean up memory
        free(nameValidation);
        nameValidation = NULL;
        
    } while(strcmp(current->type, "END_ROOM") != 0);
    
    // clean up memory
    free(current);
    free(myHouse);
    myHouse = NULL;
    current = NULL;
        
    // victory!    
    printf("\nYOU HAVE FOUND THE END ROOM. CONGRATULATIONS!\n");
    printf(" %i steps were taken, your path was:\n", steps);
    printf("%s", path);
    printf("\n");
    
    return 0;
}
//end method main
//**************************************************************************************************