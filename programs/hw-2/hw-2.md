# Assignment 2
- `cp /home/tburger/comp280/tracks.dat .`
- `cp /home/tburger/comp280/tracks2.dat .`
- `od -t x1 tracks.dat`
    - need to tell it how you would like to see the data
    - you can tell it how many bytes you want to see in each line

- `man od`
- `od -t x1 tracks.dat`
- `od -t x1 -t a tracks.dat`
    - ASCII format
- `od -t x1 -t a -t f4 tracks.dat`
    - Floating point numbers
- `-t`
    - Adds another line to the format when it is printed out
- 4 = int
- 2 = short
- 5 = does not always have a null character
```
0 9 _hex
0000 1001 _binary

0000 10(01) = id // and misc with 3 gives you two bits
0000 (10)01 = category
000(0) 1001 = Engaged // shift over 4 bits "and" it with a 1: it is a 1 bit field, so you only need 1 bit. Mask value of one
0000 1001 = 
```
- Learn how to open a binary file
    - Bucket of bytes
    - Read in 16 bytes at a time
    - `fread`: Reads in 16 bytes and reutrns how much it it actually read
    - Use this to create structure bytes

- %s how to limit number of characters to be print and set to 5

## Important
- Will be reading in a 16 byte record
- `rb`: open a binary file
- `void * ptr`: Can pass address
- `size_t size`: "I got a thing thats 16 bytes
- `size_t nmemb`: Read 1 record at a time
- `fread`: Will give you back 1 if something to read 0 if nothing to read

### Extracting and Setting Bits
- `0x3F` = 6 bits = 111111
    - Also called a mask
- `0xF` = 4 bits = 1111
- `0x` means that it is a hexadecimal value
- print out sizeof your structure, should be 16 bytes

![SC](img/Screenshot%202024-09-25%20at%204.04.15%20PM.png)

### Bit Fields

### How to Add Data to a Packed Structure
