/*  struct node {
     int data;
     node* left;
     node* right;
    } 
    */

    /* void insert(node** tree, int data) */
insert:
    push %ebp
    mov %esp, %ebp

    mov 8(%ebp), %eax
while:
    mov (%eax), %ecx
    test %ecx, %ecx
    jz alloc_node

    mov (%ecx), %edx
    cmp 12(%ebp), %edx
    jl right_node
    
    lea 4(%ecx), %eax
    jmp while

right_node:
    lea 8(%ecx), %eax
    jmp while


/*  while (*tree) {
      int this = (*tree)->data;
      if (data < this) {
          tree = &(*tree)->right;
      } else {
          tree = &(*tree)->left;
      }
} */

alloc_node:
    push %edi
    mov %eax, %edi

    push $12
    push $1
    call calloc
    add $8, %esp
    
    push %esi
    mov 12(%ebp), %esi
    mov %esi, (%eax)
    pop %esi

    mov %eax, (%edi)

    pop %edi
    mov %ebp, %esp
    pop %ebp
    ret


print_and_free:
    push %ebp
    mov %esp, %ebp
    push %esi

    mov 8(%ebp), %esi
    test %esi, %esi
    jz 1f

    push 4(%esi)
    call print_and_free
    call free
    add $4, %esp

    push (%esi)
    push $pfmt
    call printf
    add $8, %esp

    push 8(%esi)
    call print_and_free
    call free
    add $4, %esp

1:
    pop %esi
    leave
    ret


    .global main
main:
    push %ebp
    mov %esp, %ebp
    
1:
    // scanf("%d", &x)
    push $x
    push $sfmt
    call scanf
    add $8, %esp

    cmp $1, %eax
    jne 2f

    push x
    push $tree
    call insert
    add $8, %esp

    jmp 1b

2:
    push tree
    call print_and_free
    
    mov %ebp, %esp
    pop %ebp
    ret

sfmt:
    .asciz "%d"
pfmt:
    .asciz "%d\n"

    .data
x:  
    .int 0
tree:
    .int 0
