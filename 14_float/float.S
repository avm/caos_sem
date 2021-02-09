   
    .global calculate
calculate:
    push %ebp
    mov %esp, %ebp

    movsd 8(%esp), %xmm0
    movsd 16(%esp), %xmm1

    mulsd %xmm0, %xmm0
    mulsd %xmm1, %xmm1
    addsd %xmm1, %xmm0
    sqrtsd %xmm0, %xmm0

    mov 24(%esp), %eax
    movsd %xmm0, (%eax)

    leave
    ret
