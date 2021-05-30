#include <stdio.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <sys/mman.h>

struct Node {
    int value;
    int count;
    struct Node *left;
    struct Node *right;
};

void push(struct Node **root, int val) {
    if (!*root) {
        if ((*root = calloc(1, sizeof(struct Node))) < 0) {
            exit(1);
        }
        (*root)->value = val;
        (*root)->count = 1;
        (*root)->left = NULL;
        (*root)->right = NULL;
        
        return;
    } else if (val < (*root)->value) {
        push(&((*root)->left), val);
    } else if (val > (*root)->value) {
        push(&((*root)->right), val);
    } else {
        ++((*root)->count);
    }
    return;
}

void free_tree(struct Node **root) {
    if (*root) {
        free_tree(&((*root)->left));
        free_tree(&((*root)->right));
        free(*root);
        *root = NULL;
    }
}

void find_min_commonest(struct Node *node, int *maxcnt_minval) {
    if (!node) {
        return;
    }
    int max_count = maxcnt_minval[0],
        min_val = maxcnt_minval[1];
    if (node->count > max_count) {
        max_count = node->count;
        min_val = node->value;
    } else if (node->count == max_count && node->value < min_val) {
        min_val = node->value;
    }
    maxcnt_minval[0] = max_count;
    maxcnt_minval[1] = min_val;
    find_min_commonest(node->left, maxcnt_minval);
    find_min_commonest(node->right, maxcnt_minval);
}

typedef struct thread_data {
    struct Node **root;
    int *begin;
    int *end;
    pthread_t id;
} td;

void *func(void *arg) {
    td data = *(td *)(arg); 
    int len = 0;
    for (int *cur = data.begin; cur != data.end; ++cur, ++len) {
        push(data.root, *cur);
    }
    printf("len: %d\n", len);
}

int main(int argc, char *argv[]) { 
    if (argc != 3) {
        return 1;
    }
    
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        return 1;
    }
    int n = atoi(argv[2]);

    struct stat statbuf;
    if (fstat(fd, &statbuf) < 0) {
        return 1;
    }
    int *map = (int *) mmap(NULL, statbuf.st_size, PROT_READ, MAP_SHARED, fd, 0);
    struct Node *root = NULL;

    td threads[n];

    off_t tmp = statbuf.st_size / sizeof(int) / n;
    for (int i = 0; i < n; ++i ){ 
        threads[i].root = &root;
        threads[i].begin = (i == 0 ? map : threads[i-1].end); 
        threads[i].end = (i == n-1 ? map + statbuf.st_size / sizeof(int) : map + (i+1) * tmp);
        if (pthread_create(&threads[i].id, NULL, func, &threads[i]) != 0) {
            return 1;
        }

    }

    for (int i = 0; i < n; ++i) {
        pthread_join(threads[i].id, NULL);
    }
    
    int mm[2] = { 0, 0 };
    find_min_commonest(root, mm);
    printf("%d %d\n", mm[0], mm[1]);
    
    free_tree(&root);
    return 0;
}
