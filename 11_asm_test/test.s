    .text
    .global main
main:
    call func1
    cmp $3, %eax
    jz do_not_print
    call writei32
do_not_print:
    ret

    .data
x:
    .int 42


    .text
func1:
    push %ebp
    mov %esp, %ebp

    // esp-> [local vars] [ret] ....
    sub $4, %esp
    // (%esp)  ==  -4(%ebp)

    mov %esp, %eax
    call readi32
    mov %eax, -4(%ebp)
    //...
    mov (%esp), %eax
    add $4, %esp
    pop %ebp  
    ret
