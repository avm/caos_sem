#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(void) {
	int N = 0;

	if (scanf("%d", &N) != 1) {
		return 1;
	}

	for (int i = 1; i <= N; ++i) {
        if (i == N) {
            printf("%d\n", i);
            return 1;
        }
        pid_t child = fork();
		if (child < 0) {
			perror("fork failed");
			return 2;
		}

		if (child > 0) {
			// Parent
            printf("%d ", i);
            fflush(stdout);
            int status = 0;
			waitpid(child, &status, 0);
            if (WEXITSTATUS(status) != 0) {
                if (i == 1) {
                    printf("some child failed\n");
                }
                return 42;
            }
            break;
		}
	}
}
