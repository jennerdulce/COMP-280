# Bash Programming
- replace replace print command with `execute` command
1. test program:
    - sleep 60
    - use ps command to find process
    - use kill command to kill
2. exit code of 13
    - int
    - return 13
3. 
    - Sleep 1
    - return exit code 0
4. cd
    - ls
    - cd /
        - uses chdir to change directory
        - cd goes back to home directory when no arguments
        - using chdir. need to implement `echo $HOME`
        - get env -> pass into chdir
        - 2 arguments, 1 parameter to cd command
        - print out error message if more than 1 argument
    - ls: this one should print out different list than the first
5. ctrl-C does not kill shell
    - print ctrl-c was entered while not killing process

- `execvp` to search path with name given it
- replace contents of child process with new program

- if you have job running in foreground
- parent process with waitpid specificying process id of child and wait to finish
- & in end = background
    - do not waitpid