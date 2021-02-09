    .global main
main:
    mov $'y', %eax
    mov %al, hello_array

    push $hello_array
    call puts
    add $4, %esp

    incl hello_const
    mov hello_const, %eax
    movzb (%eax), %eax
    push %eax
    call putchar
    add $4, %esp

    push $'\n'
    call putchar
    add $4, %esp

    movl $bar+36, bar+28

    xor %eax, %eax
    ret

    .data
hello_array:
    .asciz "hello"
hello2:
    .asciz "hello"
hello_const:
    .int str_const_1
bar:
    .skip 72, 0

    .text
str_const_1:
    .asciz "hello"
