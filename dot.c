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
    return 0;
}
