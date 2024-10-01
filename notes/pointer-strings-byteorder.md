# Pointer, Strings, Byte Order

## Pointer
- `malloc()` allocates how much memry you would like
- `free()` give memory back to the system
    - You have to free space after using it
- `calloc()`
- You cannot count that all memory is set to 0
- Calling '3' on the same pointer is bad news
- 

## String

## Byte Order
- Network Byte Order deals with endian conversions
- A lot of old network protocols were done on sun systems
- Sun microsystems based off motorola processors based off big endian machines
    - Sun microsystems developed Java
- C# Developed microsoft
    - Microsoft processors are little endian
- Most processors are little endian are because x86 is common
- Short, Int, Long Int, Float, and Double are all affected by byte order.

- Built in functions to convert
```c
#include <arpa/inet.h>
uint32_t htonl(unit32_t hostlong);
uint16_t htonl(unit16_t hostshort);
uint32_t ntonl(unit32_t netlong);
uint16_t ntonl(unit16_t netshort);
```

### Check Endianness
```c
short var = 1;
char * ptr2Byte = (char *_ &var);
bool isLittleEndian = (*ptr2Byte == 1);
```
- If is 1, little endian
- Big endian value would be 00 followed by 01