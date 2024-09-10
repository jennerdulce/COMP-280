
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