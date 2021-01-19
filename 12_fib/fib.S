    .text
    .global main
main:
    call readi32
    movl $1, %ebx
    movl $1, %ecx

while:
    cmp $0, %eax
    jl print
    addl %ebx, %ecx
    xchg %ebx, %ecx
    dec %eax
    jmp while

print:
    movl %ecx, %eax
    call writei32
    call nl
    xor %eax, %eax
    call finish
