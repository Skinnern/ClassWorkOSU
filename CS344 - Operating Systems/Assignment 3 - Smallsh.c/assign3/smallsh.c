//skinnern
//5/26/2017
//cs344
//smallsh.c
//to compile:
//gcc smallsh.c -o smallsh
//to run:
//./p3testscript>2&1 | more


//imports for project
#define _GNU_SOURCE
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>




//**************************************************************************************************
//begin child_list
//struct to contain children
struct child_list {
    //current number contained
	unsigned int num;
	//maximum number contained
    unsigned int cap;
	//pid_t is a signed int type which is used to represent a process ID
	//in this instance, we are creating a process_id that is a pointer of the children
    pid_t *children;
		
} bg_child_list; //end child_list, call the background children list
//end child_list
//**************************************************************************************************




//**************************************************************************************************
//methods to run
int shell_status = 0;
//run our main loop
//this will collect information needed to carry out the read and execute method
void main_running_loop();
//create file token prep, to make sure it will be ready to create
char* create_file_token(char **word, unsigned int max_length);
//prep our main method that will carry out the actions given by the user
void read_and_execute(char *line, unsigned int length);
//remove comments that may exist within the program
bool remove_comment(char *word);
//send interrupt signal
void trap_interrupt(int signum);
//prep printing the user's arguments for the console
void print_user_args(const char **arr);
//end the child
void end_child(int signum);
//initalize the list of children for the program
void initialize_child_list();
//will remove the child's list from the program
void remove_child_list();
//push initiation
void push_list_child(pid_t child);
//pop initation
pid_t pop_list_child();
//end methods to run
//**************************************************************************************************




//**************************************************************************************************
//begin initialize_child_list
//initalize the child processes in the background
void initialize_child_list() {
	//current number of background items for our struct is zero
    bg_child_list.num = 0;
	//maximum total of background processes for our struct is 4
    bg_child_list.cap = 4;
	//this will set the children in our struct to be the process id that was assigned
    bg_child_list.children = malloc(bg_child_list.cap * sizeof(pid_t));
}//end initialize_child_list()
//end initialize_child_list
//**************************************************************************************************




//**************************************************************************************************
//begin remove_child_list
//destory all of the child lists that currently exist
void remove_child_list() {
	//use free() to free the memory associated with the stack
    free(bg_child_list.children);
}//end remove_child_list()
//end remove_child_list
//**************************************************************************************************




//**************************************************************************************************
//begin push_list_child
 //push child process onto the stack of all child processes
void push_list_child(pid_t child) {
	//if num of children is the same as the cap
    if (bg_child_list.num == bg_child_list.cap) {
		//double the cap
        bg_child_list.cap *= 2;
		//realloc memory needed for the arrays
        bg_child_list.children = realloc(bg_child_list.children,
                        bg_child_list.cap * sizeof(pid_t));
    }//end if
	//set the child into its respective position on the array
    bg_child_list.children[bg_child_list.num] = child;
	//increment the number on bg_child_list
    bg_child_list.num++;
}//end method
//end push_list_child
//***more comments
//**************************************************************************************************




//**************************************************************************************************
//begin pop_list_child
//pop bakcground process off of the stack
pid_t pop_list_child() {
	//if loop, check if null before popping first
    if (bg_child_list.num > 0) {
		//remove the end child, completing the pop
        bg_child_list.num--;
		//return the bg_child_list with the number of children
        return bg_child_list.children[bg_child_list.num + 1];
        }//end if
		//if number in bg_child_list is 0, dont do anything 
		else {
		//return 0, was not able to pop
        return 0;
    }//end else
}//end method
//end pop_list_child
//**************************************************************************************************




//**************************************************************************************************
//begin main
//main process
int main() {
	//initalize the child list
    initialize_child_list();
    //trap sigint because we're creating a shell, 
	//so we would want to kill the children processes and not the current process
    signal(SIGINT, trap_interrupt);
	//end the child
    signal(SIGCHLD, end_child);
    //call back to our main running loop
	main_running_loop();
	//return 0
    return 0;
}
//end main
//**************************************************************************************************




//**************************************************************************************************
//begin trap_interrupt
//trap a signal and kill all the child processes
void trap_interrupt(int _) {
	//creat int child status
	//will use this to kill child
    int child_status;
	//create new pid_t named child
	//will use this to kill child
	//this acts as a point of reference to the child
    pid_t child;
	//while child is being popped off of the stack of children
    while ((child = pop_list_child())) {
		//kill current child grabbed by the while loop
        kill(child, SIGKILL);
		//wait for the child process 
        waitpid(child, &child_status, 0);
    }//end while
}//end method
//end trap_interrupt
//**************************************************************************************************




//**************************************************************************************************
//begin was_bgd
//will determine whether or not a process had been run in the background
//bool, as all we need to know is true or false on whether the individual process had been run in the background
bool was_bgd(pid_t pid) {
	//for loop using the current number of children in the struct to iterate
    for (int i = 0; i < bg_child_list.num; i++) {
		//if statement to check equivalance between the process id, and the list of background children that we had used
        if (pid == bg_child_list.children[i]) {
			//return process as one that had been running in the background
            return true;
        }//end if
    }//end for
	//return false catch if the process did not meet the requirements to be run in the background
    return false;
}//end bool was_bgd
//end was_bgd
//**************************************************************************************************




//**************************************************************************************************
//begin end_child
//signal trap to intercept the sigchld, if child was backgrounded, we will print its exit status, and the pid it used
void end_child(int signum) {
	//create int child info
    int child_info;
	//wait for the child process
    pid_t pid = waitpid(0, &child_info, 0);
	//if child process had been backgrounded
    if (was_bgd(pid)) {
		//print the pid the child used
        printf("%d\n%d\n", pid, WEXITSTATUS(child_info));
    }//end if 
}//end method
//end end_child
//**************************************************************************************************




//**************************************************************************************************
//begin main_running_loop
//readloop method will wait for input to the line, it will parse and 
//then execute the item until it reaches the end of file 
void main_running_loop() {
		//create a character line pointer as null, to prepare for user input
		//this will be needed to create an array of the user input, and read what is being said
		//plans to implement: 
		//line pointer for input
        //size_t for size of process
		char *line = NULL;
		//size_t is an unsigned integral type
        size_t linecap = 0;
		//ssize_t represents a signed version of sigh_t where it represents the size 
		//of the blocks that can be read or written in a single operation
        ssize_t line_len;
        //print a colon to give indication to the user that the program is ready for input
		printf(":");
		//while loop holding calls to run the program, we use a comparitor to zero to make sure that 
		//the user's inputs are greater than zero, if they are zero we will destroy the children
        while ((line_len = getline(&line, &linecap, stdin)) > 0) {
                read_and_execute(line, (unsigned int)line_len);
                printf(":");
                fflush(stdout);
        }//end while
		//destory the child list if the user gives an empty input
        remove_child_list();
}//end method
//end main_running_loop
//**************************************************************************************************




//**************************************************************************************************
//begin read_and_execute
//this will parse a given line and then attempt to execute it
//****************NEEDS MORE COMMENTS******************************
void read_and_execute(char *line, unsigned int length) {
	//need to follow the following layout
    //command [arg1 arg2 ...] [< input_file] [> output_file] [&]

	//we want to make it so that there are never more arguments 
	//than there are characters that are read from the line provided by the user
    //the following will add our arguments to a pointer of args
	char **args = malloc(length * sizeof(char*));

	//list of charactersthat seperate the arguments given to a command
	//ignore quotes, newline will remove trailing if we get stuck in a trail on the previous line
        const char *sep = " \n";
	//create char array to store 
    const char devnull[] = "/dev/null";
	//infile will be the fileno
    int infile = STDIN_FILENO;
	//outfile will be the fileno
    int outfile = STDOUT_FILENO;
	//create pid_t pid to manage processes and children
    pid_t pid;
	//initiate pointers
	//initiate word pointer
    char *word = NULL;
	//initiate input pointer
    char *input = NULL;
	//initiate output pointer
    char *output = NULL;
	//initate bool variable as false, determined if the process runs in the background at a later point.
    bool is_background = false;
	//**************************************************************************************************
    unsigned int args_index = 1;
	//
    char *command = strtok(line, sep);
    if (command == NULL) goto cleanup;
    args[0] = command;
	//using the built in exit command, we will clean up and exit with value 0
    if (strcmp(command, "exit") == 0) {
        trap_interrupt(-1);
        remove_child_list();
        free(args);
        free(line);
        exit(0);
    } else if (strcmp(command, "cd") == 0) {
        //using the cd command.
        //we get next token
        char *dest = strtok(NULL, sep);
		//check next token, if null, set the destination to $home
        if (dest == NULL) {
            dest = getenv("HOME");
        }// end if
        //change directory to destination.
        if(chdir(dest) == -1) {
            perror("chdir");
            goto cleanup;
        }//end if 
            goto cleanup;
    } else if (strcmp(command, "status") == 0) {
		//we will use the build in status command to print the status information,
		//if the referred child is exited, we will print its status as well
        if (WIFEXITED(shell_status))
            printf("Exited: %d\n", WEXITSTATUS(shell_status));
            // If it was signalled, print the signal it received.
        if (WIFSIGNALED(shell_status))
            printf("Stop signal: %d\n", WSTOPSIG(shell_status));
				//if we terminated it, we want to print the termination signal
        if (WTERMSIG(shell_status))
			printf("Termination signal: %d\n",
                                WTERMSIG(shell_status));
			goto cleanup;
		}

        //in each argument in the command given.
		do {
			word = strtok(NULL, sep);
            //if the word is NULL, finish
            if (word == NULL) {
                break;
            } else if (remove_comment(word)) {
                //if the word has a comment, remove the comment
                //then we will add the uncommented word to the arguments.
                args[args_index] = word;
				//increment argument index
                args_index++;
                    break;
					//break and end if, remove comments
            } else if (strncmp(word, "<", 1) == 0) {
                //if infile is specified, we will get the input file name.
                word = strtok(NULL, sep);
				//check for null 
                if (word == NULL) {
                    printf("Invalid syntax. "
                        "No input file provided\n");
						//end process and clean up
                    goto cleanup;
                }
                input = create_file_token(&word, length);
                continue;
            } else if (strncmp(word, ">", 1) == 0) {
                // If the outfile is specified, get the output file
                // name.
                word = strtok(NULL, sep);
                if (word == NULL) {
                    printf("Invalid syntax. "
                            "No output file provided\n");
                    //clean up after running
					goto cleanup;
                }
				//our output will use the create file token to create 
				//a file with the appropriate content and length 
                output = create_file_token(&word, length);
                continue;
            } else if (strncmp(word, "&", 1) == 0) {
                //if the process is signed with an &, we will background the process
                is_background = true;
                break;
        }
		//we will push the given word onto our list of arguments, and increase the index
        args[args_index] = word;
        args_index++;
    } while (word != NULL);
        //we will add trailing null pointer.
        args[args_index] = NULL;

        if (is_background && input == NULL) {
            // we will redirect to /dev/null
            input = (char*)devnull;
        }
        if (is_background && output == NULL) {
            // we will redirect to /dev/null
            output = (char*)devnull;
        }

		//fork the program creating two branches
		//parent will get child's pid, and child's pid is set to 0
        pid = fork();
        if (pid == 0) {
			//if the input file was specified, we will set the child's stdin to input
            if (input != NULL) {
                //attempt to open the input file
                infile = open(input, O_RDONLY);
                //if opening file failed, we will print the reason why
                if (infile == -1) {
					//print the reason for failure
                    perror("infile");
                    free(args);
                    free(line);
                    remove_child_list();
                    //exit with value 1
                    exit(1);
				//else
                } else {
                //redirect the stdin to the input file descriptor ,and then close the file
                dup2(infile, STDIN_FILENO);
                close(infile);
            }
        }
        if (output != NULL) {
			//if it doesn'e exist, create and open the output file
            outfile = open(output, O_WRONLY | O_CREAT, 0744);
            //if a failure happens opening the file, we will print the error
            if (outfile == -1) {
                perror("outfile");
                free(args);
                free(line);
                remove_child_list();
                //exit with value 1
                exit(1);
            }//end if 
            if (output != devnull) {
				//set permissions for the file
				//if output not in out devnull area, we will set it to have permissions
				//equal to that of chmod 0644
                if (chmod(output, S_IRUSR | S_IWUSR | S_IRGRP |
                    S_IROTH) == -1) {
                        perror("chmod");
                }//end if
            }//end if
			//redirect the output file's descriptor to stdout.
			
            dup2(outfile, STDOUT_FILENO);
			//close the outfile when this completes
            close(outfile);
        }//end if

        //we will attempt to execute the command, if the execution is successful,
        //then this program will be replaced by the executed one.
        execvp(command, args);
        //if execution fails, print the error, clean up allocated
        //memory, and exit.
		//intercept and interprit the value of error message
        perror("execvp");
		//clear up the arguments
        free(args);
		//clear up the line
        free(line);
		//remove the child from the list
        remove_child_list();
        // we will exit w/ value 1
        exit(1);
    } else { // parent
        // If the child process is not in the background
		//we will wait for it
        if (!is_background) {
			//wait for process
            waitpid(pid, &shell_status, 0);
			//begin else
        } else {
			//else, add it to a list of backgrounded processes
			//needs to be signaled to be let out

            push_list_child(pid);
        }// end if/else
    }
	//time to cleanup
    cleanup:
	//cleaning the input and output
	//as long as the input was not statically allocated, we will
	//free //dev/null
    if (input != devnull) {
		//free the input
        free(input);
    }//end if
	//as long as the output is not statically allocated, we will
	//free //dev/null
    if (output != devnull) {
        //free the output
		free(output);
    }//end if
    //free up the current list of arguments
    free(args);
}//end method
//end read_and_execute
//**************************************************************************************************




//**************************************************************************************************
//begin print_user_args
//print list of arguments
void print_user_args(const char **arr) {
	//for position in pointer is not null
    for (int i = 0; arr[i] != NULL; i++) {
		//print the value at char arr[i] as a string
        printf("%s, ", arr[i]);
	} //end for loop
    //return to next line
	printf("\n");
}//end void print_user_args
//end print_user_args
//**************************************************************************************************




//**************************************************************************************************
//begin remove_comment
//if exists, change # to \0
//bool for t/f, will return true if it possesses #, and change value in the word[i] position
bool remove_comment(char *word) {
	//for loop to iterate through the entire word scanning for # symbol
        for (int i = 0; word[i] != '\0'; i++) {
			//if word[i]'s contents are a #
                if (word[i] == '#') {
						//change the item in position i to \0
                        word[i] = '\0';
						//return true that # existed
                        return true;
                } //end if
        } // end for
		//return that there was no #
        return false;
} //end bool_remove_comment
//end remove_comment
//**************************************************************************************************




//**************************************************************************************************
//begin create_file_token
//get the file name
char* create_file_token(char **word, unsigned int max_length) {
		//length and size of token determined by strnlen
        size_t token_length = strnlen(*word, max_length);
		//malloc for potential size of input by using token length and the size of the char
        char *token = malloc(token_length * sizeof(char));
		//copy string word and token_length into token
        strncpy(token, *word, token_length);
		//return the token with the new string value
        return token;
} //end create_file_token
//end create_file_token
//**************************************************************************************************
