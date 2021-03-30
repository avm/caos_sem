#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    long long size_sum = 0;
    for (int i = 1; i < argc; ++i) {
        char* path = argv[i];
        struct stat statbuf;
        if (lstat(path, &statbuf) == 0 &&
            statbuf.st_nlink == 1 &&
            (statbuf.st_mode & S_IFMT) == S_IFREG)
        {
            size_sum += statbuf.st_size;
        }
    }
    printf("%lld\n", size_sum);
}
