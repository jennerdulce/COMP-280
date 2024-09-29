# Binary File Reader
- `cp /home/tburger/comp280/tracks.dat .`
- `cp /home/tburger/comp280/tracks2.dat .`
- `od -t x1 tracks.dat`
- Translate binary data from a `.dat` file
- Extract data utilizing Binary / Hexdecimal conversion

## Walkthrough

### Record
- We create a structure called `Record`
- The purpose of this structure is that the contents of the Binary File will be extracted and the information will be immediately take form of this record.
- `char name[5]` is a string that is expected to be 5 letters long
- `unsigned char misc` is used to handle the misc binary portion

## Main
- `argc` counts how many files are in the terminal command
    - The count of `./bfr tracks.dat` would be 2
    - `argc` = 2
- `argc[]` is the array of files that are attached to the terminal
    - `./bfr tracks.dat tracks2.dat`
    -   0       1           2

### While loop
- `while(fread)` statement opens and reads the binary file
- `fread()`
    - We know that the size of the record is 16 bits
    - So we insert our structure that we want the information to take form of
    - `sizeof(Record)` Ensure that we dictate how much space we need for the information
    - Lastly, applying the opened file

### Handling Misc
- `record.misc`
    - This area is written in binary and needs to be broken down into hex format
    - i.e. 09 = 0000 1111
    -   000|0     |11    |11
    engaged   cat     id
    - We know that id is 2 bytes and since it sits at the front, we do not have to shift. We mask the data that we want to keep
    - `0b11` means that we want 2 binary places
    - `Category` is 2 away from the front. So we shift 2 and again keep only 2 spaces annotated by `& 0b11`
    - `Engaged` is 4 spaces away and so we shift 4 and then mask only 1 space

## latitude, longitude, altitude, name
- We extracted this data from the `tracks.dat` file and the information is translated nicely into its appropriate variables that has been laid out by our structure `Record`
- We then use this information and directly print it out

## Notes
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

### Important
- Will be reading in a 16 byte record
- `rb`: open a binary file
- `void * ptr`: Can pass address
- `size_t size`: "I got a thing thats 16 bytes"
- `size_t nmemb`: Read 1 record at a time
- `fread`: Will give you back 1 if something to read 0 if nothing to read

### Extracting and Setting Bits
- `0x3F` = 6 bits = 111111
    - Also called a mask
- `0xF` = 4 bits = 1111
- `0x` means that it is a hexadecimal value
- print out sizeof your structure, should be 16 bytes

![SC](img/Screenshot%202024-09-25%20at%204.04.15%20PM.png)
![tracks binary](img/Screenshot%202024-09-28%20at%208.14.28%20PM.png)
![Output](img/Screenshot%202024-09-28%20at%207.42.39%20PM.png)
![info](img//Screenshot%202024-09-28%20at%208.19.21%20PM.png)
![info2](img/Screenshot%202024-09-28%20at%208.19.26%20PM.png)