#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    pid_t child = fork();
    if (child < 0) {
        perror("fork");
        return 1;
    }
    if (child > 0) {
        // parent process
        waitpid(child, NULL, 0);
        printf("1\n");
    } else {
        // child process
        child = fork();
        if (child < 0) {
            perror("fork in child");
            return 1;
        }
        if (child > 0) {
            // still child
            waitpid(child, NULL, 0);
            printf("2 ");
            fflush(stdout);
        } else {
            // grandchild process
            printf("3 ");
        }
    }
}
