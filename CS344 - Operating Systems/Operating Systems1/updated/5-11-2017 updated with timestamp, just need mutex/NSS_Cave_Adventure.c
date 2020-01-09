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
//begin method writeRoomFile
void writeRoomFile(struct ConstrRoom* r, char* filename) {
    
    FILE *f;
    f = fopen(filename, "w");
    
    if (f == NULL) {
        fprintf(stderr, "Can't open input file!\n");
        exit(1);
    } 
    
    // builds the data in file
    fprintf(f,"ROOM NAME: %s\n", r->name);
    int i;
    for (i=0; i<r->connectionTotal; i++){
        fprintf(f,"CONNECTION %i: %s\n", i+1, r->connectingRooms[i]);
    }
    fprintf(f,"ROOM TYPE: %s\n", r->type);
    fclose(f);    
}
//end method writeRoomFile
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
//begin method genRandom
//generates a random number between two given numbers
//CHANGE THIS
int genRandom(int LowVal, int HighVal){
    int result=0;
    int low = 0;
    int high = 0;
    
    if(LowVal < HighVal) {
        low = LowVal;
        high = HighVal + 1;
    }
    else {
        low = HighVal;
        high = LowVal + 1;
    }
    
    result = (rand()%(high-low))+low;
    return result;
}
//end method genRandom
//**************************************************************************************************





//**************************************************************************************************
//begin method createRooms
struct ConstrRoom* createRooms(){
    
    // allocate memory for room structs
    struct ConstrRoom *house = malloc(7*sizeof(struct ConstrRoom));
    
    // assign room names
    char roomNames[10][20];
    //room 1, den
    strcpy(roomNames[0], "DEN");
	//room 2, office
    strcpy(roomNames[1], "OFFICE");
	//room 3, kitchen
    strcpy(roomNames[2], "KITCHEN");
	//room 4, bedroom
    strcpy(roomNames[3], "BEDROOM");
	//room 5, library
    strcpy(roomNames[4], "LIBRARY");
	//room 6, basement
    strcpy(roomNames[5], "BASEMENT");
	//room 7, hallway
    strcpy(roomNames[6], "HALLWAY");
	//room 8, bathroom
    strcpy(roomNames[7], "BATHROOM");
	//room 9, garage
    strcpy(roomNames[8], "GARAGE");
	//room 10, attic
    strcpy(roomNames[9], "ATTIC");
	//generate random number to determine start room
    int startRoomIndex = genRandom(0,9);
    
    // assign room ids and number of connections, set total connections to 0
    int i;
    for (i=0; i<7; i++){
		//set the total connections to zero
        house[i].connectionTotal = 0;                  // no connections made yet
		//assign names in order from random starting position
        strcpy(house[i].name, roomNames[(i+startRoomIndex)%10]);
		//set all room types to be mid room, this will be overwritten for the start room, and the end room
        strcpy(house[i].type, "MID_ROOM");
    }
    
    // generate a random number between given values for the start room
    int start_room = genRandom(0,6);
    int end_room;
    //generate random value for end room
	do{
		
        end_room = genRandom(0,6);
		//make sure that random value is not the same as the given start value
    } while (start_room == end_room);
	//edit file for start room to change type MID_ROOM to START_ROOM
    strcpy(house[start_room].type, "START_ROOM");
	//edit file for end room to change type MID_ROOM to END_ROOM
    strcpy(house[end_room].type, "END_ROOM");

    // Start making 2 way connections between rooms
    int rand;
    for (i=0; i<7; i++){
        int newConnection;
        int validConnection = 0;    // set flag to check validity, 0 = invalid, 1 = valid
        rand = genRandom(3,6);  // number of connections to make
       
        while (house[i].connectionTotal < rand) {
        
            // generate a random number, cannot be the same as the room id we are in.
            do{
                newConnection = genRandom(0,6);
            } while (newConnection == i);
            validConnection = 1;
            
            // make sure we aren't already connected to this attempted room connection
            int j;
            for (j=0; j<NumRooms; j++) {
                if (strcmp(house[i].connectingRooms[j], house[newConnection].name) == 0) {
                    validConnection = 0; // already connected to that room
                }
            }

            // check if our new connection can make anymore connections
            if (validConnection == 1 && house[newConnection].connectionTotal >= NumRooms) {
                    validConnection = 0;
                }
           
            // if passes all tests, then make connection
            if (validConnection == 1){
                strcpy(house[i].connectingRooms[house[i].connectionTotal], house[newConnection].name);
                strcpy(house[newConnection].connectingRooms[house[newConnection].connectionTotal], house[i].name);
                house[i].connectionTotal++;
                house[newConnection].connectionTotal++;
            }
        } 
    }
    return house;
}
//end method createRooms
//**************************************************************************************************





//**************************************************************************************************
//begin method createFiles
void createFiles(struct ConstrRoom* r){
  
    // get PID
    int pid;
    pid = getpid();
    
    // create buffer for file path
    char dirname[128];
    
    // builds the name of directory
    sprintf(dirname, "%s.%d", "skinnern.rooms",pid);  
        
    // check if the directory exists, if not, create it, then navigate to it
    struct stat path = {0};
    if (stat(dirname, &path) == -1) {
        mkdir(dirname, 0777);
    }
    chdir(dirname);
    
    // create the room files

    FILE *f;
    int i;
    for (i=0; i<7; i++){
        char file[10];
        strcpy(file, r[i].name);
        
        // creates the file (empty at this point)
        f = fopen(file, "w");
        if (f == NULL) {
            fprintf(stderr, "Can't open input file!\n");
        exit(1);
        }  
        fclose(f);
        
        // function writes data to file
        writeRoomFile(&r[i], file);
    }
}
//end method createFiles
//**************************************************************************************************


//**************************************************************************************************
//print time to file

void timeToFile()
{
	
    time_t current_time;
    FILE* file;
	//char file1[10];
    //strcpy(file1, "currentTime.txt");
    current_time = time(NULL);

    file = fopen("currentTime.txt", "w+");
	
	printf("%s", ctime(&current_time));
	current_time = time(NULL);
    fprintf(file, "%s", ctime(&current_time));
	 fclose(file);    

	
	
	}





//**************************************************************************************************

//**************************************************************************************************
//begin method main
//it took me at least a day to remember that main could only call on methods that were above it,
//so a good portion of my code has been modified from just being written inside the main
int main(int argc, char** argv) {

    // seed rand with current time
    srand(time(NULL));
    
    // creates the room structures from memory and saves them in structs
    struct ConstrRoom *myHouse = createRooms();
    
    // builds files from the structs and places them in a new directory
    createFiles(myHouse);
    
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
        //char ntime[]= {'T', 'i', 'm', 'e'};
		//printf("teststring: %s\n", ntime );

		//char greeting[6] = {'H', 'e', 'l', 'l', 'o', '\0'};
		//ntime[] = "Time"
        nameValidation = readRoomFile(nextLoc);
        
        // user enters an invalid name 
        if(strcmp(nameValidation->name, nextLoc) != 0){
			
			if (strcmp(nextLoc, "time") == 0){
				printf("\n\nDisplaying Date!\n\n");
				//display time
				//*********************************************************************************************
				printf("\n\nPrinting Date to file named currentTime.txt\n\n");
				timeToFile();
				//write time to file
				//*********************************************************************************************
			}
			else{
			//printf("I like cheese more.");
			printf("\nHUH? I DON’T UNDERSTAND THAT ROOM. TRY AGAIN.\n\n");
			}
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
