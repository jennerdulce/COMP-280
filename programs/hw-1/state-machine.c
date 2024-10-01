// Assignment exercising states, switch, entering files, testing, and reading files.
// cp /home/tburger/comp280/sloc_test_cases/* .
// rm sloc.c
// vim sloc.c
// gcc -o sloc sloc.c -Wall

// ./sloc tc5.c
// 1 2 tc5.c

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
int semicolonActualCount;
int totalLines;
int totalSloc;

// States
enum states {
	normal_state,
	character_literal_found_state,
	comment_found_state,
	escape_string_state,
	escape_char_literal_state,
	escape_comment_state,
	multiline_comment_found_state,
	slash_found_state,
	star_found_state,
	string_found_state,
};

enum states currentState = normal_state;

// Processing Functions
void ProcessCharacterLiteral(char ch){
	switch (ch) {
    	case '\\': currentState = escape_char_literal_state; break;
    	case '`': currentState = normal_state; break;
    	default: break;
	}
}

void ProcessEscapeCharLiteral(char ch){
	switch (ch) {
    	default: currentState = character_literal_found_state;
	}
}

void ProcessEscapeString(char ch){
	switch (ch) {
    	default: currentState = string_found_state;
	}
}

void ProcessStar(char ch){
	switch (ch){
    	case '/':
        	currentState = normal_state;
        	break;
    	default: currentState = multiline_comment_found_state;
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
    	case '\\':
        	currentState = escape_string_state;
        	break;
    	default: break;
	}
}

void ProcessSlash(char ch){
	switch (ch){
    	case '*':
        	currentState = multiline_comment_found_state;
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
        	currentState = normal_state;
	}

	switch (ch) {
    	default: break;
	}
}

void ProcessMultilineComment(char ch){
	switch (ch) {
    	case '*': currentState = star_found_state; break;
    	default: break;
	}
}

void ProcessNormalCharacter(char ch){
    
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
    	case '`':
        	currentState = character_literal_found_state; break;
    	default: currentState = normal_state; break;
	}
}

void ProcessChar(char ch){
	int numCh = (int) ch;
    	if(numCh == 10){
        	lineCount++;
	}

	switch (currentState){
    	case normal_state:
        	ProcessNormalCharacter(ch);
        	break;
    	case character_literal_found_state:
        	ProcessCharacterLiteral(ch);
        	break;
    	case comment_found_state:
        	ProcessComment(ch);
        	break;
    	case escape_string_state:
        	ProcessEscapeString(ch);
        	break;
    	case escape_char_literal_state:
        	ProcessEscapeCharLiteral(ch);
        	break;
    	case multiline_comment_found_state:
        	ProcessMultilineComment(ch);
        	break;
    	case slash_found_state:
        	ProcessSlash(ch);
        	break;
    	case star_found_state:
        	ProcessStar(ch);
        	break;
    	case string_found_state:
        	ProcessString(ch);
        	break;
    	default:
        	printf("Unhandled state\n");
        	break;
	}
}

void ProcessFile(FILE * f){
	int ch = fgetc(f);
	while(ch != EOF){
    	ProcessChar(ch);
    	ch = fgetc(f);
	}
}

// Main function
int main(int argc, char * argv[]){
	if(argc == 1){
    	ProcessFile(stdin);
    	printf("%d %d\n", semicolonActualCount, lineCount);
	} else if (argc == 2){
    	FILE * f = fopen(argv[1], "r");
        	if(f == NULL){
            	perror("Error: No file found.");
            	return 1;
        	} else {
            	ProcessFile(f);
            	printf("%d %d %s\n", semicolonActualCount, lineCount, argv[1]);
        	}
	} else {
    	for(int i = 1; i < argc; i++){
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
