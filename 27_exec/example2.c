#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int mysys(const char *command) {
    pid_t proc_pid = fork();
    if (proc_pid == -1) {
        return -1;
    } else if (!proc_pid) {
        execl("/bin/sh", "sh", "-c", command, (char *) NULL);
        _exit(127);
    } else {
        int status;
        if (waitpid(proc_pid, &status, 0) == -1) {
            return 127;
        }
        if (WIFEXITED(status)) {
            return WEXITSTATUS(status);
        } else if (WIFSIGNALED(status)) {
            return WTERMSIG(status) + 128;
        }
        return 127;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        exit(1);
    }
    printf("!%d\n", mysys(argv[1]));
    return 0;
}
