    .text
    .global main
main:
    call readi32
    movl $1, %ebx
    movl $1, %ecx
    mov $0, %edx

    mov $x, %esi

while:
    cmp $0, %eax
    jl print
    addl %ebx, %ecx
    mov %ecx, (%esi, %edx, 4) // esi + edx*4
    mov x, %edi   // load data from memory
    mov $x, %edi  // store address in register
    inc %edx
    xchg %ebx, %ecx
    dec %eax
    jmp while

print:
    movl %ecx, %eax
    call writei32
    call nl
    xor %eax, %eax
    call finish

    .data
x:
    .space 4*100, 0
