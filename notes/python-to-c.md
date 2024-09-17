
```c
#include <stdio.h>
int main()
{
    printf("Hello, World!\n");
    return 0
}
```
- One source file, have a main function

## Command Line Parameters
- `ls -l`: -l is a parameter to the main procedure
- `int argc`
- `char* argv[]`

## C Language
 ```c 
int countOfStudents = 42;
double averageTestScore = 1.2;
int examScore = 0;
examScore = ++examScore;


```

### Define Symbolic Constants

```c
#define NAME value
#define PI 3.1415926
#define MAX_NAME_LENGTH 60
#define AREA (SIDE_LENGTH 12)
#include <stdio.h>
int main()
{
    printf("Hello, World!\n");
    return 0
}
```
- Lifetime and Visibility of variables can be controlled
- Lifetime (Global): Whole execution
- Visible (Global): Visibility from spot of declaration to end of file

### Example C Code
```c
#include <stdio.h>
#define NUM_CASES 10
int samples[NUM_CASES];
void readSamples(){}
int analyzeSamples(){}
int main(int argc, char * argv[])
{
    printf("Hello, World!\n");
    return 0
}
```

### How to compile C Program on terminal
- `vim hello.c`
    - opening a 'c' file using vim editor
- `gcc -o hello hello.c -Wall`
    - I want to call the file to be compiled "hello"
    - `hello.c`: file to be opened
    - `-Wall`: Enable reporting of all warnings
- `./hello`: runs the program

### Typecast

```c
int i ;
double = 3.14
int num = (int) double
```

### sizeof
- `sizeof (int)`

### Compound Assignment
- `A += B` is the same as `A = A + B`

### Handling readonly
- `:w!`

### Functions
- Need return statement within a function if you want to return a result
- Also you need to the identify the 'type' the function needs to be in front of the function
```c
int add(int a, int b){
    return a + b;
}
```

### Compound Statement
- Code block // Group of statements
```c
{
    a = 3;
    b = 4;
}
```

### Switch Statement
```c
switch (linePosition)
{
    case 1:
    // do this
    break;
    case 2:

}
```

### While
```c
count = 0;
while (count < 5) {
    data[count] = 3
    ++ count
}
```

### For
```c
int count;
for(count = 0; count < 5; ++count){
    data[count] = 3;

}
```

### Do While
- Similar to while, WILL ALWAYS EXECUTE ONCE
```c
int value;
do {
    printf("HI")
    scanf("%d", &value);
} while (value < 5);
```

### Continue and Break
- `break`: Gets out of Loop
- `continue`: Continues the loop but skipping that particular iteration and whatever is after it within the code block