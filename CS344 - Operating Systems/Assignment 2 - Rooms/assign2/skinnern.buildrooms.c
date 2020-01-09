#include <stdio.h>
#include <stdlib.h>
#include <string.h>         
#include <unistd.h>         // gets PID to name dir
#include <fcntl.h>          // creating dir
#include <time.h>           // seeding srand
// DEFINING SOME MACROS
#define NumRooms 6
#define BUFFER_SIZE 512




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
    
    //create buffer for file path
    char dirname[128];
    
    //builds the name of the skinnern.rooms directory
    sprintf(dirname, "%s.%d", "skinnern.rooms",pid);  
        //was appended with ,pid
		//and prefixed with "%s.%d", 
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









int main(int argc, char** argv) {

    // seed rand with current time
    srand(time(NULL));
    
    // creates the room structures from memory and saves them in structs
    struct ConstrRoom *myHouse = createRooms();
    
    // builds files from the structs and places them in a new directory
    createFiles(myHouse);
}