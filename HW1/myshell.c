#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 100
#define HISTORY_SIZE 100
#define FALSE 0
#define TRUE 1

int main(void)
{   
    close(2);
    dup(1);
    char command[BUFFER_SIZE];
    
    // Initialize history as a HISTORY_SIZE x BUFFER_SIZE array
    char history[HISTORY_SIZE][BUFFER_SIZE] = {0};

    // Will be used to track where we are on the history.
    int curr_history = 0;

    
    while (1)
    {
        fprintf(stdout, "my-shell> ");
        memset(command, 0, BUFFER_SIZE);
        fgets(command, BUFFER_SIZE, stdin);

        // This case isn't written really in the exercise.
        // This is put here for better generality.

        if(curr_history >= HISTORY_SIZE) {
            perror("error");
            exit(1);
        }
        

        
        // Divide into command only
        char* command_only = strtok(command, " \n");

        if(strncmp(command_only, "exit", 4) == 0)
        {
            break;
        }
   
        // Parameters will be used as argv for execvp
        char* parameters[BUFFER_SIZE];

        // Must start with the command.
        parameters[0] = command_only;
        
        // Will be used to split into strings between spaces.
        char* command_split = strtok(NULL, " \n");
        int j = 1;

        while(command_split) {
            // Put current string into parameters.
            parameters[j++] = command_split;
            
            // If you use NULL, it continues from where it was.
            command_split = strtok(NULL, " \n");
        }


        if (command_only != NULL) {

            // Create a space seperated string
            char full_command[BUFFER_SIZE] = {0};
            for (int k = 0; k < j; k++) {
                strcat(full_command, parameters[k]);
                if (k < j - 1) {
                    strcat(full_command, " ");
                }
            }
            // Push into history the space seperated command
            strcpy(history[curr_history++], full_command);

        } else {

            // Command is empty
            strcpy(history[curr_history++], "");
            continue;
        }
            
        if(strncmp(command_only, "history", 7) == 0) {
            // History detected, start printing top down
            for(int i = curr_history - 1; i >= 0; i--) {
                fprintf(stdout,"%d %s\n", i + 1, history[i]);
            }
            continue;
        }
        // Need to put NULL at end so execvp recognizes it.
        parameters[j] = NULL;
        int is_background = 0;

        // Check if "&" is present and mark it null too.
        if (j > 0)
        {
            is_background = strcmp(parameters[j - 1],"&") == 0;
            if (is_background) {
                // Mark & as end, its not a parameter
                parameters[j - 1] = NULL;
            }
        }


        pid_t pid = fork();

        // Fork failed
        if (pid < 0) {
            perror("error");
            exit(1);
        }
        else if(pid == 0) {
            if (execvp( command_only, parameters) < 0) {
                // Failed
                continue;
            }
        } else {
            // Fork successful and we are the parent
            if (!is_background) {
                waitpid(pid, NULL, 0);
            }
        }
    }

    return 0;
}
