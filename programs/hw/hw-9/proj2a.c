int main(int argc, const char **argv){
    char cmdline[MAX_LINE_LENGTH];
    struct CommandLine command;
    for(;;){
        printf("hw-9> ");
        fgets(cmdline, MAX_LINE_LENGTH, stdin);
        if(cmdline[0] == '\n'){
            continue;
        }
        if(parse_command_line(cmdline, &command) == -1){
            printf("Error: invalid command\n");
            continue;
        }
        if(strcmp(command.argv[0], "exit") == 0){
            break;
        }
        if(strcmp(command.argv[0], "cd") == 0){
            if(chdir(command.argv[1]) == -1){
                printf("Error: %s\n", strerror(errno));
            }
            continue;
        }
        if(fork() == 0){
            execvp(command.argv[0], command.argv);
            printf("Error: %s\n", strerror(errno));
            exit(1);
        }
        wait(NULL);
    }
}