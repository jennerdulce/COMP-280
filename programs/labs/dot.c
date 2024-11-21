// Write the program in C
// Write a dot('.') to the screen once a second
// When a ctrl-c is pressed, the applciation writes a '!' to the screen and exits
// Dont do any output from the signal handler

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int stop = 0;

void handle_sigint(int sig) {
    stop = 1;
}

int main() {
    // Register signal handler for SIGINT (Ctrl-C)
    signal(SIGINT, handle_sigint);

    while (!stop) {
        // Write a dot ('.') to the screen
        printf(".");
        fflush(stdout);

        // Sleep for one second
        sleep(1);
    }

    // Write a '!' to the screen and exit
    printf("!\n");
    fflush(stdout);
    return 0;
}