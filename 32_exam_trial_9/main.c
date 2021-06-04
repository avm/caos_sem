#include <inttypes.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/signalfd.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

enum { FINISHCODE = -1, ERROR = 1 };

volatile int child;

void handlerALRM(int signal) {
    char buff[20];
    sprintf(buff, "%s%d%s", "/proc/", child, "/status");
    int fd = open(buff, O_RDONLY);
    FILE* file = fdopen(fd, "r");
    size_t n = 0;
    char* lineptr = NULL;
    int cnt = 0;
    while (getline(&lineptr, &n, file) != -1) {
        if (++cnt == 3 || cnt == 22) {
            printf("%s", lineptr);
        }
    }
    fclose(file);
    free(lineptr);
    fflush(stdout);
    kill(child, SIGKILL);
    waitpid(child, NULL, 0);
    exit(0);
}

int main(int argc, char* argv[]) {
    struct sigaction actALRM = {};
    actALRM.sa_flags = SA_RESTART;
    actALRM.sa_handler = handlerALRM;
    sigaction(SIGALRM, &actALRM, NULL);

    int64_t intervalMSEC = 100000;
    struct itimerval to = {};
    to.it_value.tv_usec = intervalMSEC;
    to.it_interval.tv_usec = intervalMSEC;
    setitimer(ITIMER_REAL, &to, NULL);

    child = fork();
    if (child < 0) {
        fprintf(stderr, "fork error\n");
        exit(ERROR);
    }
    if (child == 0) {
        execlp(argv[1], argv[1], NULL);
        fprintf(stderr, "exec error\n");
        exit(ERROR);
    }
    pause();
}

