// Assignment exercising states, switch, entering files, testing, and reading files.
// cp /home/tburger/comp280/sloc_test_cases/* .
// rm sloc.c
// vim sloc.c
// gcc -o sloc sloc.c -Wall
// ./sloc tc*.c

// OUTPUT:
// 0 2 tc1.c
// 0 2 tc2.c
// 1 2 tc3.c
// 1 2 tc4.c
// 1 2 tc5.c
// 2 6 tc6.c
// 3 2 tc7.c
// 8 18 Total

#include <stdio.h>

// Global Variables
int lineCount;
int semicolonCount;
int semicolonActualCount;
int prevCh;
int totalLines;
int totalSloc;

// States
enum states {
    normal_state,

    character_literal_found_state,
    comment_found_state,
    escape_found_state,
    multiline_comment_found_state,
    slash_found_state,
    star_found_state,
    string_found_state,

    finish_state
};

enum states currentState = normal_state;
enum states previousState = normal_state;

// Processing Functions
void ProcessCharacterLiteral(char ch){
    switch (ch) {
        case '\\': previousState = currentState; currentState = escape_found_state; break;
        case '`': currentState = normal_state; break;
        case ';': 
            ++semicolonCount; 
            break;
        default: break;
    }
}

void ProcessEscape(char ch){
    switch (previousState){
        case normal_state:
            if(ch == 'n'){
                ++lineCount;
            }
            currentState = normal_state;
            previousState = normal_state;
            break;
        case string_found_state:
            if(ch == 'n'){
                ++lineCount;
            }
            currentState = string_found_state;
            previousState = normal_state;
            break;
        case character_literal_found_state:
            if(ch == 'n'){
                ++lineCount;
            }
            currentState = character_literal_found_state; 
            previousState = normal_state;
            break;
        case comment_found_state:
            if(prevCh == '\\' && ch == 'n'){
                ++lineCount;
                currentState = normal_state;
                previousState = normal_state;
            }
            break;
        case multiline_comment_found_state:
            if(prevCh == '\\' && ch == 'n'){
                ++lineCount;
                currentState = multiline_comment_found_state;
                previousState = normal_state;
            }
            break;
        default: 

            break;
    }

    switch (ch) {
        default: break;
    }
}

void ProcessStar(char ch){
    switch (ch){
        case '/': 
            currentState = normal_state; 
            break;
        default: currentState = normal_state;
    }   
}

void ProcessString(char ch){
    switch (ch) {
        case '"': 
            currentState = normal_state; 
            break;
        case '\'': 
            currentState = normal_state; 
            break;
        case ';': 
            ++semicolonCount; 
            break;
        case '\\': 
            previousState = currentState; 
            currentState = escape_found_state; 
            break;
        default: break;
    }
}

void ProcessSlash(char ch){
    switch (ch){
        case '*': 
            currentState =     multiline_comment_found_state; 
            break;
        case '/': 
            currentState = comment_found_state; 
            break;
        default: currentState = normal_state;
    }   
}

void ProcessComment(char ch){
    int numCh = (int) ch;
    if(numCh == 10){
        lineCount++;
        currentState = normal_state;
    }

    switch (ch) {
        case ';':
            ++semicolonCount; 
            break;
        case '\\': 
            previousState = comment_found_state; currentState = escape_found_state; 
            break;
        default: break;
    }
}

void ProcessMultilineComment(char ch){
    int numCh = (int) ch;
    if(numCh == 10){
        lineCount++;
    }

    switch (ch) {
        case '*': currentState = star_found_state; break;
        case ';': ++semicolonCount; break;
        case '\\': 
            previousState = multiline_comment_found_state; currentState = escape_found_state; 
            break;
        default: break;
    }
}

void ProcessNormalCharacter(char ch){
    int numCh = (int) ch;
    if(numCh == 10){
        lineCount++;
    }

    switch (ch) {
        case '"': 
            currentState = string_found_state; 
            break;
        case '\'': 
            currentState = string_found_state; 
            break; 
        case '/': 
            currentState = slash_found_state;  
            break;
        case ';': ++semicolonActualCount;
            break;
        case '\\': 
            previousState = currentState; 
            currentState = escape_found_state; 
            break;
        case '`':
            currentState = character_literal_found_state; break; 
        default: currentState = normal_state; break;
    }
}

void ProcessChar(char ch){
    // printf("Current Char: %c \n", ch);
    // printf("Current Char: %d \n", (int) ch);
    switch (currentState){
        case normal_state:
            // printf("in a\n");
            ProcessNormalCharacter(ch);
            break;
        case character_literal_found_state:
            // printf("in b\n");
            ProcessCharacterLiteral(ch);
            break;
        case comment_found_state:
            // printf("in c\n");
            ProcessComment(ch);
            break;
        case escape_found_state:
            // printf("in d\n");
            ProcessEscape(ch);
            break;
        case multiline_comment_found_state:
            // printf("in e\n");
            ProcessMultilineComment(ch);
            break;
        case slash_found_state:
            // printf("in f\n");
            ProcessSlash(ch);
            break;
        case star_found_state:
            // printf("in g\n");
            ProcessStar(ch);
            break;
        case string_found_state:
            // printf("in h\n");
            ProcessString(ch);
            break;
        case finish_state: break;
        default:
            printf("Unhandled state\n");
            break;
    }
}

void ProcessFile(FILE * f){
    int ch = fgetc(f);
    // printf("Current Char: %c \n", (char) ch);
    while(ch != EOF){
        ProcessChar(ch);
        prevCh = ch;
        ch = fgetc(f);
    }
}

// Main function
int main(int argc, char * argv[]){
    if(argc == 1){
        ProcessFile(stdin);
        printf("%d %d\n", semicolonActualCount, lineCount);
    } else {
        for(int i = 1; i < argc; i++){ // Remove if necessary
            FILE * f = fopen(argv[i], "r");
            if(f == NULL){
                perror("Error: No file found.");
                return 1;
            } else {
                ProcessFile(f);
            }
            printf("%d %d %s\n", semicolonActualCount, lineCount, argv[i]);
            totalLines += lineCount;
            totalSloc += semicolonActualCount;
            lineCount = 0;
            semicolonActualCount = 0;
        }
        if(argc >= 3){
            printf("%d %d Total\n", totalSloc, totalLines );
        }
    }
    return 0;
}