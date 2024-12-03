#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "command_line.h" // Include the header file for parseLine and freeCommand
#include <signal.h>
#define MAX_LINE_LENGTH 512 // Maximum length of a command line
//signal handlers
void handle_sigint(int sig) { // SIGINT is sent by pressing Ctrl+C
}
void handle_sigchld(int sig) { // SIGCHLD is sent when a child process terminates
int status;
while (waitpid(-1, &status, WNOHANG) > 0) {
if (WIFEXITED(status)) { // If the child exited normally

printf("Child exited normally with exit code %d\n", WEXITSTATUS(status)); // Print the exit code
} else if (WIFSIGNALED(status)) { // If the child was terminated by a signal
printf("Child terminated by signal %d\n", WTERMSIG(status)); // Print the signal number
} else {
printf("Child terminated for an unknown reason\n"); // If the child terminated for an unknown
reason
}
}
}
int main(int argc, const char **argv) {
char cmdline[MAX_LINE_LENGTH]; // Buffer to store the command line
struct CommandLine command; // Structure to store the parsed command, part of command_line.h
// Set up signal handlers
signal(SIGINT, handle_sigint);
signal(SIGCHLD, handle_sigchld);
for (;;) { // Infinite loop, same as while(1)
// Exit the shell if EOF (Ctrl+D) is encountered
if (feof(stdin)) { // feof(stdin) returns true if EOF is encountered
exit(0);
}
printf("> "); // Print the prompt
// Read the command line
if (fgets(cmdline, sizeof(cmdline), stdin) == NULL) {
if (feof(stdin)) { // Check again for EOF after fgets
exit(0);
}
perror("fgets");
continue;
}
bool gotLine = parseLine(&command, cmdline); // Parse the command line
if (gotLine) {
// Handle "exit" command
if (command.argCount > 0 && strcmp(command.arguments[0], "exit") == 0) {
freeCommand(&command);
break;
}
// Handle "cd" command
if (command.argCount > 0 && strcmp(command.arguments[0], "cd") == 0) { // If the command is
"cd"
if (command.argCount == 1) { // If the number of arguments is less than 2
chdir(getenv("HOME")); // Change directory to HOME
}else if(command.argCount == 2){ // If the number of arguments is 2
if (chdir(command.arguments[1]) != 0) { // If chdir fails
perror("cd"); // Print an error message
}
}else{ // if there are more than 2 arguments
printf("too many arguments");
}

} else { // If the command is not "cd"
// Fork and execute external commands
pid_t pid = fork();
if (pid == 0) {
// Child process
execvp(command.arguments[0], command.arguments);
perror("execvp"); // If execvp fails
exit(EXIT_FAILURE);
} else if (pid > 0) {
if (command.background) {
printf("Started background process %d\n", pid);
} else {
waitpid(pid, NULL, 0); // Wait for the foreground process, reap the child
}
} else {
perror("fork"); // If fork fails
}
}
// Free memory allocated for the command
freeCommand(&command);
}
}
return 0;