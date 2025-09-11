#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    //number of characters in the input, does this have a limit?
    char line[9999];
    char *tokens[999];
    int pid; //forking id

    //while(1) makes it keep running 
    while (1) {
        //shell prompt, isnt this like $ in other shells?
        printf(">");
        //to my understanding, this makes the > appear first
        fflush(stdout);

        //checks input to see if its null, if so, break
        if (fgets(line, sizeof(line), stdin) == NULL){
            break;
        }

        //Remove newline
        line[strcspn(line, "\n")] = '\0';

        char *token ; //to store words
        char *rest = line; //tracks position
        int i = 0; //num of tokens

        //tokenize using strsep
        while ((token = strsep(&rest, " \t")) != NULL) {
            if (*token == '\0') {
                //if token is empty, it skips it
                continue;
            }
            args[i++] = token; 
        }
        args[i] = NULL; 

        //loop again if there is nothing
        if (i == 0) {
            continue;
        }

        //child
        pid = fork();
        if (pid == 0) {
            //supposed to replace child with args[0] ?
            execvp(args[0], args);
            //this prints if an error is occured
            perror("child failed");
            exit(1);
            //parent process here
        } else (pid > 0) {
            //if pid > 0, parent waits
            wait(NULL);
        } 
    }
    return 0;
}