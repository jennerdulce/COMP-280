# Structured Types
- Simple: Single value that you put into a variable of that type

## Two Kinds of Structured Types
- Similar to an object
- `Structure`: A collection of components
- `Array`: A collection of components of the same type

```c
struct Point{
    int x;
    int y;
}

struct Point upper_left;
struct Point upper_left = {10, 20};
upper_left.x = 12;
```

### Triangle Structure
```c
struct Triangle{
    struct Point v1;
    struct Point v2;
    struct Point v3;
};

struct Triangle right_triangle;
right_triangle.v1.x = 13;
```

### Arrays
- A structured type where all components are of the same type
- Componenets are accessed by an idex
```c
int vector[10];
vector[3] = 1234;
double matrix [3][3];
matrix[0][1] = 5.2
```