#include <asm/unistd_32.h>

    .global _start
_start:
    mov $__NR_read, %eax
    mov $0, %ebx
    mov $buf, %ecx
    mov $64, %edx
    int $0x80

    test %eax, %eax
    jl exit

    mov %eax, %edx

    test %eax, %eax
loop:
    jz print
    mov buf-1(%eax), %cl
    cmp $'z', %cl
    ja 1f
    cmp $'a', %cl
    jb 1f
    add $('A' - 'a'), %cl
    mov %cl, buf-1(%eax)
1:  
    dec %eax
    jmp loop
    
print:
    mov $__NR_write, %eax
    mov $1, %ebx
    mov $buf, %ecx
    int $0x80

exit:
    mov $__NR_exit, %eax
    mov $0, %ebx
    int $0x80 

    .data
buf:
    .skip 64
