#include "command_line.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 512

int main(int argc, const char **argv)
{
    char cmdline[MAX_LINE_LENGTH];
    struct CommandLine command;
    for (;;)
    {
        printf("> ");
        fgets(cmdline, MAX_LINE_LENGTH, stdin);
        if (feof(stdin)) 
        {
            exit(0);
        }

        bool gotLine = parseLine(&command, cmdline);
        if (gotLine) 
        {
            printCommand(&command);
            freeCommand(&command);
        }
    }
}
