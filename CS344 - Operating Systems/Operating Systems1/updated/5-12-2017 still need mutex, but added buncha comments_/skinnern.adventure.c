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
		//iterate through connecting rooms
        if(i+1 < r->connectionTotal)        
            printf("%s, ",r->connectingRooms[i]);
        else if (i+1 == r->connectionTotal)
            printf("%s.\n",r->connectingRooms[i]);
    }
	//give user prompt to input values
    printf("WHERE TO? >");         
}
//end method printRoom
//**************************************************************************************************





//**************************************************************************************************
//begin method writeRoomFile
void writeRoomFile(struct ConstrRoom* r, char* filename) {
    
	//create file pointer
    FILE *f;
	//open the filename argument
    f = fopen(filename, "w");
    //check if file exists, might be a permission issue, or file was deleted if it does not display
    if (f == NULL) {
		//error message if unable to read
        fprintf(stderr, "Can't open input file!\n");
        //exit if error is recieved
		exit(1);
    } 
    
    //places data into file
    fprintf(f,"ROOM NAME: %s\n", r->name);
	//loop to iterate through the connections that the file displays
    int i;
    for (i=0; i<r->connectionTotal; i++){
        fprintf(f,"CONNECTION %i: %s\n", i+1, r->connectingRooms[i]);
    }
	//
    fprintf(f,"ROOM TYPE: %s\n", r->type);
    //close connection to file so it is saved and has contents when we click on it while its running
	fclose(f);    
}
//end method writeRoomFile
//**************************************************************************************************





//**************************************************************************************************
//begin method readRoomFile
struct ConstrRoom* readRoomFile(char* inputFile){
	//create file pointer
    FILE* f;
	//open file with write permissions
    f = fopen(inputFile, "r");
	//create line buffer for reading inputs
    char line[BUFFER_SIZE];
    //allocate space for struct
    struct ConstrRoom *r = malloc(sizeof(struct ConstrRoom));
	//reset connection total to zero
    r->connectionTotal = 0;
    
    char* token;
    
    // parses the file, line by line and builds a ConstrRoom struct
    if (f) {
        while(fgets(line,BUFFER_SIZE,f)) {
            //searches for ' ' delimiter 
            token = strtok(line, " ");
            //continue while the token is not null
            while (token != NULL ){
                //parse through information we do not require, but acts as a tag for what we need
                if (strcmp("ROOM", token) == 0){
					//continue while token is not null
                    token = strtok(NULL, " ");
                    // continue parsing past delimeter
                    if(strcmp("NAME:", token) == 0){
						//continue parsing
                        token = strtok(NULL, "\n");
                        //copy the room name to our struct
						strcpy(r->name, token);
						//break for next line scan
                        break;
                    }
                    //get the room's room_type
                    if(strcmp("TYPE:", token) == 0){
						//we've already parsed out room, and now we act if it says type, if so, we will pass through
                        token = strtok(NULL, "\n");
						//copy the token for our room type into our struct
                        strcpy(r->type, token);
						//break to read the next line
                        break;
                    }
                }
                //get the connections that the room has
                if (strcmp("CONNECTION", token) == 0){
					//searches for '' delimiter
                    token = strtok(NULL, " ");
                    //token is now an int, as the connection value is a number
                    int i = atoi(token);
					//using i to set up our index
                    i--; 
					//
                    token = strtok(NULL, "\n");
					//copy our string from our token into our connecting rooms struct array
                    strcpy(r->connectingRooms[i], token);
					//increase the number of connections in the connectionTotal struct array
                    r->connectionTotal++;
                    break;                    
                }
            }
        }
	//close our file connection
    fclose(f);
    }
	//return our struct to be further acted on
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
//
int genRandom(int LowVal, int HighVal){
	//declare variables
    int result=0;
    int low = 0;
    int high = 0;
    //compare that lowVal is lower than highVal, if this is the case, assign low and high to proper variables 
    if(LowVal < HighVal) {
		//low will remain low in this case
        low = LowVal;
		//high will remain high in this case
        high = HighVal + 1;
    }
	//if not true, low value will be the high, and high will be the low
    else {
		//assign higher value to highval
        low = HighVal;
		//assign lower value to lowval
        high = LowVal + 1;
    }
    //generate random number as variable result
    result = (rand()%(high-low))+low;
	//return random variable between those two values
    return result;
}
//end method genRandom
//**************************************************************************************************





//**************************************************************************************************
//begin method createRooms
struct ConstrRoom* createRooms(){
    
    //allocate memory for room structs
    struct ConstrRoom *house = malloc(7*sizeof(struct ConstrRoom));
    
    // assign room names
    char roomNames[10][20];
    //room 1, ATTIC
    strcpy(roomNames[0], "ATTIC");
	//room 2, BATHROOM
    strcpy(roomNames[1], "BATHROOM");
	//room 3, BEDROOM
    strcpy(roomNames[2], "BEDROOM");
	//room 4, DECK
    strcpy(roomNames[3], "DECK");
	//room 5, DEN
    strcpy(roomNames[4], "DEN");
	//room 6, GARAGE
    strcpy(roomNames[5], "GARAGE");
	//room 7, HALLWAY
    strcpy(roomNames[6], "HALLWAY");
	//room 8, KITCHEN
    strcpy(roomNames[7], "KITCHEN");
	//room 9, OFFICE
    strcpy(roomNames[8], "OFFICE");
	//room 10, STUDY
    strcpy(roomNames[9], "STUDY");
	//generate random number to determine start room
    int startRoomIndex = genRandom(0,9);
    
    //assign the room ids and number of connections
    int i;
    for (i=0; i<7; i++){
		//set the total connections to zero, as no connections exist yet
        house[i].connectionTotal = 0;                  
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
        int validConnection = 0;    //set flag to check validity, 0 = invalid, 1 = valid
        rand = genRandom(3,6);  //number of connections to make
       //iterate through a predetermined number of times to add connections to each value
       while (house[i].connectionTotal < rand) {
        
            //generate a random number, cannot be the same as the room id we are in.
            do{
				//generate random number, this will be used to determine the rooms that conect to the current file
                newConnection = genRandom(0,6);
            } 
			
			while (newConnection == i);
            validConnection = 1;
            
            //make sure we aren't already connected to this attempted room connection
            int j;
            for (j=0; j<NumRooms; j++) {
				//compare strings of of names of rooms, if a conection already exists, that is not a valid connection
                if (strcmp(house[i].connectingRooms[j], house[newConnection].name) == 0) {
					//set to an invalid connection, as we are already connected to that room
                    validConnection = 0;
                }
            }

            //check if our new connection can make anymore connections
            if (validConnection == 1 && house[newConnection].connectionTotal >= NumRooms) {
                    validConnection = 0;
                }
           
            // if passes all tests, then make connection
            if (validConnection == 1){
				//copy string house[newConnection].name into our house struct
                strcpy(house[i].connectingRooms[house[i].connectionTotal], house[newConnection].name);
				//copy house[i].name into our house struct
                strcpy(house[newConnection].connectingRooms[house[newConnection].connectionTotal], house[i].name);
				//increment connection total to loop through and gain all connections
                house[i].connectionTotal++;
				//increment connection total to increment the total number of connections a file has
                house[newConnection].connectionTotal++;
            }
        //end while
		} 
	//end for
	}
    return house;
}
//end method createRooms
//**************************************************************************************************





//**************************************************************************************************
//not used
//would read files contained in a directory, changed my method to do this and this code is no longer used
/*
int FileTestRead(void)
{
	int i=0;
	
	char dirname[128];
    
    // builds the name of directory
    sprintf(dirname,"skinnern.rooms");  
	FILE * f;
	f = fopen(dirname, "r");
    
	
	DIR *d;
    struct dirent *dir;
    d = opendir("skinnern.rooms");
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            printf("%s\n", dir->d_name);
			 
        }
        closedir(d);
    }
    return(0);
}
*/
//**************************************************************************************************





//**************************************************************************************************
//begin method createFiles
void createFiles(struct ConstrRoom* r){
  
    //get PID
    int pid;
    pid = getpid();
    
    //create buffer for file path
    char dirname[128];
    
    //builds the name of the skinnern.rooms directory
    sprintf(dirname, "%s.%d", "skinnern.rooms",pid);  
        
    //check if the directory exists, if not, create it, then navigate to it
    struct stat path = {0};
    if (stat(dirname, &path) == -1) {
        mkdir(dirname, 0777);
    }
	//chdir to the dir name, now we are reading and writing from this skinnern.rooms directory
    chdir(dirname);
    
    //create the room files
	//create file pointer
    FILE *f;
	//begin loop to iterate through all 7 files
    int i;
    for (i=0; i<7; i++){
        char file[10];
		//copy string r[[i].name to file, to be written to the file]
        strcpy(file, r[i].name);
        
        // creates the file with the program having write access(empty at this point)
        f = fopen(file, "w");
        //error check if file exists
		
		if (f == NULL) {
			//should only proc if it does not have permissions to make/read the file, or if file is deleted
            fprintf(stderr, "Can't open input file!\n");
			//if it is unable to read, exit from the process
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
    //create file pointer
	FILE* file;
	//char file1[10];
    //strcpy(file1, "currentTime.txt");
    current_time = time(NULL);
	//open file currentTime.txt with write permissions
    file = fopen("currentTime.txt", "w+");
	//print the current time into the console for the user to seed
	printf("%s", ctime(&current_time));
	
	current_time = time(NULL);
    //print current_time to file
	fprintf(file, "%s", ctime(&current_time));
	//close file, so that users are able to see the data
	fclose(file);    

	
	
	}
//**************************************************************************************************





//**************************************************************************************************
//begin method main
//it took me at least a day to remember that main could only call on methods that were above it,
//so a good portion of my code has been modified from just being written inside the main
int main(int argc, char** argv) {

    //seed the rand with current time
    srand(time(NULL));
    
    //creates the room structures from memory and saves them in structs
    struct ConstrRoom *myHouse = createRooms();
    
    //uses the createfiles method to build files from the structs and places them in a new directory
    createFiles(myHouse);
    
    //use the findStart method to search for the starting room and copy the name of the room
    struct ConstrRoom *startRoom = findStart(myHouse);
    char startName[20];
	//copy string startroom->name to our startname
    strcpy(startName, startRoom->name);

    //room pointers that are used in game loop   
    struct ConstrRoom *current;
    struct ConstrRoom *nameValidation;

    //variables to count steps and the path from start to finish
    int steps = 0;
    char path[BUFFER_SIZE];

    //set starting location
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
				//if user chooses time instead of a location, we will print out time onto the console, and to a file named currentTime.txt
				printf("\n\nPrinting Date to file named currentTime.txt\n\n");
				//calls method to write to file
				timeToFile();
				//write time to file
			}
			else{
			//printf("I like cheese more.");
			printf("\nHUH? I DON’T UNDERSTAND THAT ROOM. TRY AGAIN.\n\n");
			}
        }
        
        //user enters name of the current room
        else if(strcmp(current->name, nextLoc) == 0){
            printf("\n");
        }
        
        // user has entered a valid input
        else {
            //builds path taken string and increases steps taken
			//concats path to string
            strcat(path, current->name);
			//appends a new line to the path string so that it is readable when printed to the user
            strcat(path, "\n");
            steps++;
            
            //clean up
            free(current);
            
            //move to the next location
            current = readRoomFile(nextLoc);
            printf("\n");
        }
        
        //clean up memory
        free(nameValidation);
		//set to null to ensure clean
        nameValidation = NULL;
        
    } 
	//when user reaches the END_ROOM
	while(strcmp(current->type, "END_ROOM") != 0);
    
    //clean up current
    free(current);
	//clean up myHouse
    free(myHouse);
	//set to null to ensure clean
    myHouse = NULL;
	//set to null to ensure clean
    current = NULL;
        
    //player won, display messages including: Steps taken, victory message, the path   
	//normal win screen
    printf("\nYOU HAVE FOUND THE END ROOM. CONGRATULATIONS!\n");
    //player path = number of steps they took, found using out steps loop
	printf(" %i steps were taken, your path was:\n", steps);
	//shows the path by taking our path and printing into string
    printf("%s", path);
    printf("\n");
    //return main
    return 0;
}
//end method main
//**************************************************************************************************
