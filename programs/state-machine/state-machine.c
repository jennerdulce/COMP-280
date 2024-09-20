// ./sm < input
// cat input
// echo takes from stdin (standard input)
    // echo 1 0 -25 | ./quad
// https://campuswire.com/c/GE8D46705/lectures/20

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
        case ' ':
        case '!':
        case '"': 
        case '#':
        case '$':
        case '%':
        case '&':
        case '\'':
        case '(':
        case ')':
        case '*':
        case '+':
        case ',':
        case '-':
        case '.':
        case '/':
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case ':':
        case ';': 
            ++semicolonCount; 
            break;
        case '<':
        case '=':
        case '>':
        case '?':
        case '@':
        case 'A':
        case 'B':
        case 'C':
        case 'D':
        case 'E':
        case 'F':
        case 'G':
        case 'H':
        case 'I':
        case 'J':
        case 'K':
        case 'L':
        case 'M':
        case 'N':
        case 'O':
        case 'P':
        case 'Q':
        case 'R':
        case 'S':
        case 'T':
        case 'U':
        case 'V':
        case 'W':
        case 'X':
        case 'Y':
        case 'Z':
        case '[':
        case '\\': previousState = currentState; currentState = escape_found_state; break;
        case ']':
        case '^':
        case '_':
        case '`': currentState = normal_state; break;
        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'e':
        case 'f':
        case 'g':
        case 'h':
        case 'i':
        case 'j':
        case 'k':
        case 'l':
        case 'm':
        case 'n':
        case 'o':
        case 'p':
        case 'q':
        case 'r':
        case 's':
        case 't':
        case 'u':
        case 'v':
        case 'w':
        case 'x':
        case 'y':
        case 'z':
        case '{':
        case '|':
        case '}':
        case '~':
        default: currentState = normal_state;
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
        case string_found_state:
            if(ch == 'n'){
                ++lineCount;
            }
            currentState = string_found_state;
            previousState = normal_state;
        // case character_literal_found_state:
        //     if(ch == 'n'){
        //         ++lineCount;
        //     }
        //     currentState = character_literal_found_state; 
        //     previousState = normal_state;
        case comment_found_state:
            if(prevCh == '\\' && ch == 'n'){
                ++lineCount;
                currentState = normal_state;
                previousState = normal_state;
            }
        case multiline_comment_found_state:
            if(prevCh == '\\' && ch == 'n'){
                ++lineCount;
                currentState = multiline_comment_found_state;
                previousState = normal_state;
            }
        default: 
            // currentState = string_found_state;
            // previousState = normal_state;
            break;
    }

    switch (ch) {
        case ' ':
        case '!':
        case '"':
        case '#':
        case '$':
        case '%':
        case '&':
        case '\'':
        case '(':
        case ')':
        case '*':
        case '+':
        case ',':
        case '-':
        case '.':
        case '/':
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case ':':
        case ';':
        case '<':
        case '=':
        case '>':
        case '?':
        case '@':
        case 'A':
        case 'B':
        case 'C':
        case 'D':
        case 'E':
        case 'F':
        case 'G':
        case 'H':
        case 'I':
        case 'J':
        case 'K':
        case 'L':
        case 'M':
        case 'N':
        case 'O':
        case 'P':
        case 'Q':
        case 'R':
        case 'S':
        case 'T':
        case 'U':
        case 'V':
        case 'W':
        case 'X':
        case 'Y':
        case 'Z':
        case '[':
        case '\\':
        case ']':
        case '^':
        case '_':
        case '`': 
        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'e':
        case 'f':
        case 'g':
        case 'h':
        case 'i':
        case 'j':
        case 'k':
        case 'l':
        case 'm':
        case 'n':
        case 'o':
        case 'p':
        case 'q':
        case 'r':
        case 's':
        case 't':
        case 'u':
        case 'v':
        case 'w':
        case 'x':
        case 'y':
        case 'z':
        case '{':
        case '|':
        case '}':
        case '~': break;
        default: currentState = normal_state;
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
        case ' ':
        case '!':
        case '#':
        case '$':
        case '%':
        case '&':
        case '(':
        case ')':
        case '*':
        case '+':
        case ',':
        case '-':
        case '.':
        case '/':
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case ':':
        case '<':
        case '=':
        case '>':
        case '?':
        case '@':
        case 'A':
        case 'B':
        case 'C':
        case 'D':
        case 'E':
        case 'F':
        case 'G':
        case 'H':
        case 'I':
        case 'J':
        case 'K':
        case 'L':
        case 'M':
        case 'N':
        case 'O':
        case 'P':
        case 'Q':
        case 'R':
        case 'S':
        case 'T':
        case 'U':
        case 'V':
        case 'W':
        case 'X':
        case 'Y':
        case 'Z':
        case '[':
        case ']':
        case '^':
        case '_':
        case '`': 
        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'e':
        case 'f':
        case 'g':
        case 'h':
        case 'i':
        case 'j':
        case 'k':
        case 'l':
        case 'm':
        case 'n':
        case 'o':
        case 'p':
        case 'q':
        case 'r':
        case 's':
        case 't':
        case 'u':
        case 'v':
        case 'w':
        case 'x':
        case 'y':
        case 'z':
        case '{':
        case '|':
        case '}':
        case '~': break;
        default: currentState = normal_state;
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
        case ' ':
        case '!':
        case '"':
        case '#':
        case '$':
        case '%':
        case '&':
        case '\'':
        case '(':
        case ')':
        case '*':
        case '+':
        case ',':
        case '-':
        case '.':
        case '/':
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case ':':
        case '<':
        case '=':
        case '>':
        case '?':
        case '@':
        case 'A':
        case 'B':
        case 'C':
        case 'D':
        case 'E':
        case 'F':
        case 'G':
        case 'H':
        case 'I':
        case 'J':
        case 'K':
        case 'L':
        case 'M':
        case 'N':
        case 'O':
        case 'P':
        case 'Q':
        case 'R':
        case 'S':
        case 'T':
        case 'U':
        case 'V':
        case 'W':
        case 'X':
        case 'Y':
        case 'Z':
        case '[':
        case ']':
        case '^':
        case '_':
        case '`': 
        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'e':
        case 'f':
        case 'g':
        case 'h':
        case 'i':
        case 'j':
        case 'k':
        case 'l':
        case 'm':
        case 'n':
        case 'o':
        case 'p':
        case 'q':
        case 'r':
        case 's':
        case 't':
        case 'u':
        case 'v':
        case 'w':
        case 'x':
        case 'y':
        case 'z':
        case '{':
        case '|':
        case '}':
        case '~': break;
        default: currentState = normal_state;
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
        case ' ':
        case '!':
        case '"':
        case '#':
        case '$':
        case '%':
        case '&':
        case '\'':
        case '(':
        case ')':
        case '+':
        case ',':
        case '-':
        case '.':
        case '/':
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case ':':
        case '<':
        case '=':
        case '>':
        case '?':
        case '@':
        case 'A':
        case 'B':
        case 'C':
        case 'D':
        case 'E':
        case 'F':
        case 'G':
        case 'H':
        case 'I':
        case 'J':
        case 'K':
        case 'L':
        case 'M':
        case 'N':
        case 'O':
        case 'P':
        case 'Q':
        case 'R':
        case 'S':
        case 'T':
        case 'U':
        case 'V':
        case 'W':
        case 'X':
        case 'Y':
        case 'Z':
        case '[':
        case ']':
        case '^':
        case '_':
        case '`': 
        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'e':
        case 'f':
        case 'g':
        case 'h':
        case 'i':
        case 'j':
        case 'k':
        case 'l':
        case 'm':
        case 'n':
        case 'o':
        case 'p':
        case 'q':
        case 'r':
        case 's':
        case 't':
        case 'u':
        case 'v':
        case 'w':
        case 'x':
        case 'y':
        case 'z':
        case '{':
        case '|':
        case '}':
        case '~': break;
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
        case ' ':
        case '!':
        case '#':
        case '$':
        case '%':
        case '&':
        case '(':
        case ')':
        case '*':
        case '+':
        case ',':
        case '-':
        case '.':
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case ':':
        case '<':
        case '=':
        case '>':
        case '?':
        case '@':
        case 'A':
        case 'B':
        case 'C':
        case 'D':
        case 'E':
        case 'F':
        case 'G':
        case 'H':
        case 'I':
        case 'J':
        case 'K':
        case 'L':
        case 'M':
        case 'N':
        case 'O':
        case 'P':
        case 'Q':
        case 'R':
        case 'S':
        case 'T':
        case 'U':
        case 'V':
        case 'W':
        case 'X':
        case 'Y':
        case 'Z':
        case '[':
        case ']':
        case '^':
        case '_':
        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'e':
        case 'f':
        case 'g':
        case 'h':
        case 'i':
        case 'j':
        case 'k':
        case 'l':
        case 'm':
        case 'n':
        case 'o':
        case 'p':
        case 'q':
        case 'r':
        case 's':
        case 't':
        case 'u':
        case 'v':
        case 'w':
        case 'x':
        case 'y':
        case 'z':
        case '{':
        case '|':
        case '}':
        case '~': break;
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
    }
    printf("%d %d Total\n", totalSloc, totalLines );
   
    return 0;
}