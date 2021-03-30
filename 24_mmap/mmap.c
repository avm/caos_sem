#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>

enum { data_size = 512 };

int main(int argc, char* argv[]) {
    if (argc < 2) {
        return 1;
    }
    int fd = open(argv[1], O_RDWR | O_CREAT, S_IRWXU);
    if (fd < 0) {
        perror("open failed");
        return 2;
    }
    if (ftruncate(fd, sizeof(double) * data_size) < 0) {
        perror("ftruncate");
        return 100;
    }

    void* map = mmap(NULL, sizeof(double) * data_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (map == MAP_FAILED) {
        perror("mmap failed");
        return 3;
    }

    double* dptr = map;
    for (int i = 0; i < data_size; ++i) {
        dptr[i] = i;
    }

    if (munmap(map, sizeof(double) * data_size) < 0) {
        perror("munmap failed");
    }
    close(fd);
}
