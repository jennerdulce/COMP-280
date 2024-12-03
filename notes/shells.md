# Shells

- Bash is one of many different shell programs
- Shells are programs that allow you to run programs
    - Runs Programs
        - Allows uer to Specifcy an Executable File
        - Finds file (using PATH env variables)
        - Loads and executes Program
    - Manages Environment
        - Changes current working directory
        - Create Update Delete env variables
    - Keyboard Shortcuts
        - Tab
        - !!
        - !$
        - !xxx: call last command that started with xxx
        - Arrow Keys
        
    - COmmand History
    - Job Control
        - CTRL-Z: pause
        - bg: continue running program in background
        - fg: resume program in foreground
    - Interpret Scripts
        - #! name of interpreter
            - #!/bin/bash
        - Looping and Conditional Statements
        ```
            for i in *.c; do
                echo $i;
                head -1 $i
            done
        ```
    - Aliases
        - Allows you to create a shorthand for a command
        - alias name="command with arguments"
            - alias gcc="gcc -Wall -std=c99"
    - Customize environment
        - Bash processes the command in ~/.bash_profile when it starts
        - Add your own aliases and env variables
- Difference between shell programs are other things besides running programs
- Provide a programming language for building up job control
- Ways to manage environment
    - Can set up variables and other things
    - Convenience things
