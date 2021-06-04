#include <dirent.h>
#include <fcntl.h>
#include <inttypes.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

enum {ELF = 1179403647}; //Probably can cause problems if integer is stored in BigEndain/LittleEndian

int check_elf (char* name) {
    int fd = open(name, O_RDONLY);
    uint32_t desk;
    read(fd, &desk, sizeof(desk));
    if (desk == ELF) {
        return 1;
    }
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
            stat(full_name, &st);
            if ((S_ISREG(st.st_mode) || S_ISLNK(st.st_mode)) && check_elf(full_name)) {
                count += 1;
                //printf("%s\n", d->d_name);
            }
            free(full_name);
        }
    }
    closedir(dir);
    printf("%d\n", count);
}