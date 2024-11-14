# Reverse
- jle/jge/je/jne/js/jns/jl: signed
- jbe/jae/jb/ja Above or below: unsigned

## Optimzed code
- Variables
- edi, rdi
- sal $4 = 2^4 = 16
- subq $8, rsp: reserving space
- add $8, rsp: restoring space in order to return
- leal calculates address
- leal -1 %rdi subtracts 

## Unconditional Jump
- For loop or while loop

## Other
- movzbl checks 1 byte
- testb check to see if 0 %al %al
- movw = short
- leal (rdi, rdi, 4): rdi * (rdi * 4)
    - rdi * 5
- sall $2, %eax 2^2

- mov
    - l
    - w
    - q - 64 bit - address or int
    - z
    - w - 16 bits - short

- movzwl: extends to a long


movq %esp, %rbp
movq %esp, %rbp
movq %esp, %rbp
movq %esp, %rbp
movq %esp, %rbp
movq -8(%rbp), %rax
movq -8(%rbp), %rax
movq -8(%rbp), %rax
movq -8(%rbp), %rax
movq -8(%rbp), %rax
movq -8(%rbp), %rax
movl $18, 12(%rax)