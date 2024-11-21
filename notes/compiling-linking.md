# Compilation and Linking

## GCC
1. Preprocessor
    - Handles #includes and #defines. Expands macros.
    - Produces modified .c source
2. Compile
    - Translates C source code into ASM (.s)
3. Assemble
    - Translates ASM into an object file (.o)
4. Link 
    - Combines object files and libraries into an executable file
    - `-lm` all tags needed in order to input

## What is an object file? (.o)
- Binary file containing data and code
- Contains symbol and relocation information
- Produced when a "compile only" gcc command is used
- `gcc -o myobject.o -c mysource.c`
- ** Object files are often referred to as ELF files (executable and linkable format)

## ELF: Executable and Linkable format
- Have multiple sections
- `.text`: Machine Instructions
- `.rodata`: Read only data - String literals, cannot change during execution of program
    - Cannot write to read only data
- `.data`: Initialized global and static data
- `.bss`: Uninitialized global and static data
    - Initialized to 0
    - Will reserve space
- `.rel.text`: Relocation information for .text section symbols
- `.rel.data`: Relocation information for .data section symbols
- `.symtab`: Information about global variables and functions
- `.debug`: Present when linked with -g Option
- `.line`: Mapping between source line numbers and the machine code
- `.strtab`: String table for .symtab and .debug sections

### Symbol Information
- Not all names in a program become symbols in an ELF file
- Used by the linker to resolve external references
- Linux tool "nm" reposrts on symbols in an ELF file

![Symbol](img/Screenshot%202024-11-18%20at%207.17.33%20PM.png)
- Lowercase = private
- U = undefined
    - Linkers job to find printf

![NM Codes](img/Screenshot%202024-11-18%20at%207.19.13%20PM.png)

### Categories of Symbols
- Global: Defined in this file; available to all files
- External: Used in this file, but defined in another file
- Local: Defined and available only in this file

![Declarations](img/Screenshot%202024-11-18%20at%207.22.35%20PM.png)
- Things that do not become symbols (unless declared to be static)
    - Local Variables
    - typedef names
    - Preprocessor names

![Example](img/Screenshot%202024-11-18%20at%207.26.58%20PM.png)

### Strong vs. Weak Symbol
- Strong: corresponds to a function o initialized variable
- Weak: corresponts to an uninitialized global variable
- The same symbol can appear in multiple object files as a weak symbol
- Strong symbols must be unique
- Weak symbols can also be mapped to a strong symbol
- Mark as static

## Linker
- Combines object files into an executable file
- Symbol Resolution: Determine where external references are defined
- Relocation: Determine address for every symbol
- i.e. printf is from an #included file; linker will find it.
![Linker Error](img/Screenshot%202024-11-18%20at%207.34.23%20PM.png)
![Linker Error2](img/Screenshot%202024-11-18%20at%207.36.00%20PM.png)
![Duplicate Error](img/Screenshot%202024-11-18%20at%207.37.05%20PM.png)
![Undetected Linker Error](img/Screenshot%202024-11-18%20at%207.41.40%20PM.png)
- Do not get any warnings. Runs code with the error.

## Archive Files (.a)
- Collection of Object Files
- Linker selects Object Files from Archive if they contain a referenced symbol
- Code added to Linked Executable
- Each program has its own copy of code from the archive
- ** The main function should not be in an archive

### Create an Archive
- `ar -r archiveName objects...`
    - archiveName should end with a .a
    - objects should each end with .o

## Shared Library (.so)
- Linked together set of object files
- Library loaded when Executable starts
- Single Copy of Code
- Shared Between Programs
- Requires Position Independent Code
    - -fpic option

### Create a Shared Library
- Compiile each library source with -fpic
- Build the .so file
    - `gcc -shared -o libname.so objects`
    - have to start with lib____

### Use a Shared Library
- Link with the shared
- `gcc myprog.c -i myprog -L. -lname`
- -L directory containing library
- -l name of the library
- Set LD_LIBRARY_PATH env variable to directory where library is located
    - export LD_LIBRARY_PATH=/home/mine/libs

## The Complete Process
![Process](img/Screenshot%202024-11-18%20at%207.50.19%20PM.png)
![Create Shell](img/Screenshot%202024-11-18%20at%207.53.33%20PM.png)

- Gives link time errors when `#include .c` instead `#include .h`
