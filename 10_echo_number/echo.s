    .text
    .global main
main:
    call readi32
    call writei32
    call nl
    xor %eax, %eax
    ret
