#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "command_line.h"
#include "command_line.c"
#include <string.h>

#define MAX_LINE_LENGTH 512

void sigint_handler(int sig) {
    
}

void sigchld_handler(int sig) {
    int status;
    pid_t pid;

    // Reap completed background processes
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        if (WIFEXITED(status)) {
            printf("Background process exited with status %d\n",  WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Background process terminated by signal %d\n",  WTERMSIG(status));
        }
    }
}

void execute_command(struct CommandLine *command) {
    if (command->argCount == 0) return;

    if (strcmp(command->arguments[0], "cd") == 0) {
        // CD
        if (command->argCount < 2) {
            fprintf(stderr, "cd: missing argument\n");
        } else if (chdir(command->arguments[1]) != 0) {
            perror("cd");
        }
        
    } else {
        pid_t pid = fork();
            if (pid == 0) {
                // Child
                execvp(command->arguments[0], command->arguments);
                perror("execvp");
                exit(EXIT_FAILURE);
            } else if (pid > 0) {
                // Parent
                if (command->background) {
                    printf("Started background process %d\n", pid);
                } else {
                    waitpid(pid, NULL, 0);
                }
            } else {
                perror("fork");
        }
    }
}

int main(int argc, const char **argv) {
    char cmdline[MAX_LINE_LENGTH];
    struct CommandLine command;

    // Set up SIGINT handler
    signal(SIGINT, sigint_handler);
    signal(SIGCHLD, sigchld_handler);

    // Infinite loop
    for (;;) {
        if (feof(stdin)) {
            exit(0);
        }

        printf("> ");
        if (fgets(cmdline, MAX_LINE_LENGTH, stdin) == NULL) {
            if (feof(stdin)) {
                exit(0);
            }

            perror("fgets");
            continue;
        }

        bool gotLine = parseLine(&command, cmdline);
        if (gotLine) {
            execute_command(&command);
            freeCommand(&command);
        }
    }

    return 0;
}
