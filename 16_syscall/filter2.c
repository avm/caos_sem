#include <sys/syscall.h>
#include <unistd.h>

void myexit(int status) {
    asm("mov $1, %%eax \n"
        "mov %[Status], %%ebx \n"
        "int $0x80"
        : /* outputs */
        : /* inputs*/
        [Status] "m" (status));
}

/*
    asm (
        "assembler template"
        : outputs
        : inputs
        : clobbers
        : labels)
*/

int myread(int fd, char* buf, int size) {
    int result;
    asm("mov %[callnr], %%eax \n"
        "mov %[fd], %%ebx \n"
        "mov %[buf], %%ecx \n"
        "mov %[size], %%edx \n"
        "int $0x80 \n"
        "mov %%eax, %[result]"
        :
        [result] "=m" (result)
        :
        [callnr] "ri" (__NR_read),
        [fd] "rm" (fd),
        [buf] "rm" (buf),
        [size] "rm" (size)
        :
        "%eax", "%ebx", "%ecx", "%edx", "memory"
        );
    return result;
}

/*
In addition, the constraint string of an output must be prefixed with either = or +.

+ means that the output is actually a read-write value. The operand initially has the value contained by the expression. It's fine to read from this output operand at any point in the assembly string.
=& means that the output is an early-clobber output. Its initial value is unspecified. It is not a bug to read from an =& operand once it has been assigned a value.
= means that the output is write-only. The compiler can choose to give an = output the same location as an input: for that reason, it is usually a bug to write to it before the last instruction of your assembly snippet.
=@ccCOND is a special case of = that allows you to query the result of a condition code at the end of your assembly statement. You cannot reference a condition output in your assembly template.
*/

int mywrite(int fd, char* buf, int size) {
    int result = SYS_write;
    asm("int $0x80"
        :
        [result] "+a" (result)
        :
        [fd] "b" (fd),
        [buf] "c" (buf),
        [size] "d" (size)
        );
    return result;
}

void _start() {
    char buf[64];
    int result = myread(STDIN_FILENO, buf, 64);
    if (result > 0) {
        for (int i = 0; i < result; ++i) {
            char c = buf[i];
            if ('a' <= c && c <= 'z') {
                buf[i] = c + 'A' - 'a';
            }
        }
        mywrite(STDOUT_FILENO, buf, result);
    }
    myexit(0);
}
