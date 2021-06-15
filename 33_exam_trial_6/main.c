#include <dirent.h>
#include <fcntl.h>
#include <inttypes.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

const char ELFmagic[5] = "\x7f""ELF";

int check_elf (char* name) {
    int fd = open(name, O_RDONLY);
    if (fd < 0)
        return 0;
    uint32_t desk;
    char header[4];
    if (read(fd, header, sizeof(header)) != 4){
        close(fd);
        return 0;
    }
    if (memcmp(header, ELFmagic, 4) == 0) {
        close(fd);
        return 1;
    }
    close(fd);
    return 0;
}

int main(int argc, char *argv[]) {
    DIR* dir;
    struct dirent* d;
    char default_path[] = ".";
    char* dir_path = default_path;
    int count = 0;

    if (argc >= 2) {
        printf("%s\n", argv[1]);
        dir_path = argv[1];
    }
    dir = opendir(dir_path);
    if (dir) {
        while((d = readdir(dir)) != NULL) {
            struct stat st;
            char* full_name = (char*) malloc(strlen(dir_path) + strlen(d->d_name) + 2);
            sprintf(full_name, "%s/%s", dir_path, d->d_name);
            if (stat(full_name, &st) == 0) 
                if (S_ISREG(st.st_mode) && check_elf(full_name)) {
                    count += 1;
                }
            free(full_name);
        }
    }
    closedir(dir);
    printf("%d\n", count);
}
