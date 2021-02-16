#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <byteswap.h>


struct Node {
    int data;
    int left;
    int right;
    int len;
};


void write_be(char* buf, uint32_t i) {
    buf[0] = (i >> 24) & 0xff;
    buf[1] = (i >> 16) & 0xff;
    buf[2] = (i >> 8) & 0xff;
    buf[3] = i & 0xff;
}


void bswap_node(struct Node* node) {
    node->data = bswap_32(node->data);
    node->left = bswap_32(node->left);
    node->right = bswap_32(node->right);
    node->len = bswap_32(node->len);
}

union endianness {
    uint32_t integer;
    char bytes[4];
};

int is_little_endian() {
    union endianness e;
    e.integer = 1;
    return e.bytes[0] == 1;
}

void write_or_die(int fd, void* buf, size_t count) {
    if (write(fd, buf, count) != count) {
        perror("write failed");
        exit(1);
    }
}


void append_or_die(int fd, struct Node* node, char* string) {
    write_or_die(fd, node, sizeof(*node));
    write_or_die(fd, string, bswap_32(node->len));
}


int main(int argc, char* argv[]) {
    printf("little endian: %d\n", is_little_endian());
    if (argc != 3) {
        fprintf(stderr, "Usage: tree compile|retrieve FILE\n");
        return 1;
    }

    if (!strcmp(argv[1], "compile")) {
        int fd = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, S_IWUSR | S_IRUSR);
        if (fd < 0) {
            perror("file open failed");
            return 1;
        }

        char *string;
        int data;

        while (scanf("%ms %d", &string, &data) == 2) {
            const int len = strlen(string);
            off_t current = lseek(fd, 0, SEEK_CUR);
            if (current == 0) {
                struct Node node = {data, 0, 0, len};
                bswap_node(&node);
                append_or_die(fd, &node, string);
            } else {
                int current_node = 0;
                while (1) {
                    struct Node node;
                    pread(fd, &node, sizeof(node), current_node);
                    bswap_node(&node);
                    char* current_string = calloc(node.len + 1, sizeof(char));
                    pread(fd, current_string, node.len, current_node + sizeof(node));
                    int cmp = strcmp(string, current_string);
                    int* update_field = NULL;
                    if (cmp == 0) {
                        node.data = data;
                        bswap_node(&node);
                        pwrite(fd, &node, sizeof(node), current_node);
                        free(current_string);
                        break;
                    } else if (cmp < 0) {
                        update_field = &node.left;
                    } else {
                        update_field = &node.right;
                    }
                    if (*update_field == 0) {
                        *update_field = current;
                        bswap_node(&node);
                        pwrite(fd, &node, sizeof(node), current_node);
                        struct Node new_node = {data, 0, 0, len};
                        bswap_node(&new_node);
                        append_or_die(fd, &new_node, string);
                        free(current_string);
                        break;
                    }
                    current_node = *update_field;
                    free(current_string);
                }
            }
            free(string);
        }
    } else if (!strcmp(argv[1], "retrieve")) {
        int fd = open(argv[2], O_RDONLY);
        if (fd < 0) {
            perror("file open failed");
            return 1;
        }
        
        char *string;

        while (scanf("%ms", &string) == 1) {
            int current_node = 0;
            while (1) {
                struct Node node;
                pread(fd, &node, sizeof(node), current_node);
                bswap_node(&node);
                char* current_string = calloc(node.len + 1, sizeof(char));
                pread(fd, current_string, node.len, current_node + sizeof(node));
                int cmp = strcmp(string, current_string);
                int* update_field = NULL;
                if (cmp == 0) {
                    printf("Found data: %d\n", node.data);
                    free(current_string);
                    break;
                } else if (cmp < 0) {
                    update_field = &node.left;
                } else {
                    update_field = &node.right;
                }
                if (*update_field == 0) {
                    printf("Not found\n");
                    free(current_string);
                    break;
                }
                current_node = *update_field;
            }
            free(string);
        }
    }
}
