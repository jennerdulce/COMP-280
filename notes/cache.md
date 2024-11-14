# Cache

- Find how many sets
```
0x1120 - Cache Miss, puts set in stack
           Set 1
0001 0001 (001)(0 0000)

0x1125 - Cache Hit, line is already in cache
          Set 2
0001 0001 (001)(0 0100)

0x2320
- Kicks out 0x1125
- Conflict Miss
 0010 0011 (001)(0 0000)

0x2330
- Cache hit
0010 0011 (001)(1 0000)

0x1124
- Conflict Miss
0001 0001 (001)(0 1000)

0x2324
- Conflict Miss
0010 0011 (001)(0 0100)
```