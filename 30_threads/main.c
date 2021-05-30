#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

struct thread_data {
    int id; 
    pthread_t prev;
};

void* sleep_and_print(void* arg) {
    struct thread_data* data = arg;
    if (data->id > 0) {
        pthread_join(data->prev, NULL);
    }
    printf("%d\n", data->id);
    return NULL;
}

int main() {
    struct thread_data threads[10];
    pthread_t prev = 0;
    for (int i = 0; i < 10; ++i) {
        threads[i].id = i;
        threads[i].prev = prev;
        int res = pthread_create(&prev, NULL, sleep_and_print, &threads[i]);
        if (res != 0) {
            fprintf(stderr, "pthread_create: %s\n", strerror(res));
        }
    }
    pthread_join(prev, NULL);
}
