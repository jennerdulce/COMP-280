# Simple Types
- `sizeof(variableName)`;
```c

```

## Convention

```c
char c = 'x';

unsigned char max_byte = 255;
// Plan on using a numeric value top max_byte
```

## Boolean
- `#include <stdbool.h>`
- `bool` and `_Bool`
- false = 0
- true = 1
```c
#include <stdbool.g>
bool ending(){
    bool hasEnded = false;
    return hasEnded
}
```

# Enumeration Values
- Specific Values can be specified for the Enumerated Values
```c
enum Coin {penny = 1,
nickel = 5,
dime = 10,
quarter - 25};
```

```c
enum Coin {LITTLE_BUFFER = 1,
MEDIUM_BUFFER = 10,
LARGE_BUFFER = 1000,
DEFAULT_BUFFER = 100};
```

