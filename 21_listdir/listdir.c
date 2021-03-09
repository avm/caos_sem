#include <stdio.h>
#include <dirent.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        return 1;
    }
    DIR *dir = opendir(argv[1]);
    if (!dir) {
        perror("opendir failed");
        return 1;
    }
    int dirfd = open(argv[1], O_RDONLY);
    if (dirfd < 0) {
        perror("opening dirfd failed");
        return 1;
    }
    struct dirent *file;
    off_t sum_size = 0;

    uid_t euid = getuid();
    while ((file = readdir(dir))) {
        if (file->d_type == DT_DIR || !isupper(file->d_name[0]))
            continue;
        struct stat statbuf;
        if (fstatat(dirfd, file->d_name, &statbuf, 0) != 0) {
            perror("fstatat failed");
            return 1;
        }
        bool regular = (statbuf.st_mode & S_IFMT) == S_IFREG;
        bool owner_me = statbuf.st_uid == euid;
        if (!regular || !owner_me)
            continue;
        printf("adding size of %s\n", file->d_name);
        sum_size += statbuf.st_size;
    }

    printf("%ld\n", sum_size);
}
