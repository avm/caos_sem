#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        exit(1);
    }

    char *new_args[2] = {
            argv[1],
            NULL
    };
    int fdin = open(argv[2], O_RDONLY | O_CLOEXEC),
    fdout = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, S_IRUSR | S_IWUSR);
    if (fdin == -1 || fdout == -1) {
        exit(1);
    }
    if (dup2(fdin, STDIN_FILENO) == -1 || dup2(fdout, STDOUT_FILENO) == -1) {
        exit(1);
    }
    execvp(argv[1], new_args);

    perror("exec failed\n");
    return 0;
}