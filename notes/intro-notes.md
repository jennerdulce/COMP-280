Intro to Computer Sys Notes

Ssh jdulce@gh117dl13

Connect to VPN
Cp ~tburger/comp280/dream.txt .

- Creates dream.txt

ssh
Logs you into your account on linux lab machine

cp copies files from a place to where you want to put it “.” Is current directory

cat dream.txt
- Cat displays contents in the txt file on the terminal

more dream.txt
- More displays contents in the txt file on the terminal in chunks like a book
- Space to display more text
- Q to exit

fmt -70 dream.txt
fmt -70 dream.txt > fmtted_dream.txt
- Saves formatting into a different text file

man fmt
- Manual for “fmt”

man printf
- C also has similar manual in the language

vi fmtted_dream.txt
- Open with vi editor
- Has modes
- If you want to “change” you have to change into that mode
- Can navigate with arrow keys
- W to skip to words
- “I” = insert mode
- Escape gets out of insert mode back to default
- “/“ is find command
    - “N” while in find command finds next occurrence
- :q
    - Exits vi editor and does not save
- vimtutor: Learn 5 chapters
- grep <word> fmtted_dream.txt
    - Displays all lines that contain dream
- grep <word> fmtted_dream.txt | wc -l
    - Displays times (integer) word has occurred
- fmt -1 dream.txt | grep dream dream | wc -l

Simple commands
-ls -l
- Long listing with read and write permissions
- Admin/group/others

Pwd
- Displays current directory

Cd
- Change directory

VIM tutor notes
- X - delete
- :q - quit w/o saving
- i - insert (place cursor before the character where you want to insert)
    - Esc to exit back to normal mode
- A - append, similar to insert but only added to the end of the string
- :wq - save and exit
- vim <filename.txt> - creates a file with and opens vim editor
- Dw delete
    - 4dw immediately deletes 4 words
- “/“ find command while in editor
- “Dd” delete whole line
    - 2dd deletes 2 lines
