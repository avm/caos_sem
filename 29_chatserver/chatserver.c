#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>


int make_bound_socket(const char* service) {
    int listen_socket = socket(PF_INET6, SOCK_STREAM, 0);
    if (listen_socket < 0) {
        perror("failed to create socket");
        return -1;
    }

    struct addrinfo hints = {.ai_family=AF_INET6, .ai_socktype=SOCK_STREAM, .ai_flags=AI_PASSIVE};
    struct addrinfo *port_info = NULL;
    int gai_res;
    if ((gai_res = getaddrinfo(NULL, service, &hints, &port_info))) {
        fprintf(stderr, "failed to parse port %s: %s\n", service, gai_strerror(gai_res));
        goto mbs_err_exit;
    }

    int trueValue = 1;
    setsockopt(listen_socket, SOL_SOCKET, SO_REUSEADDR, &trueValue, sizeof(trueValue));
    if (bind(listen_socket, port_info->ai_addr, sizeof(struct sockaddr_in6)) != 0) {
        perror("failed to bind");
        goto mbs_err_exit;
    }

    freeaddrinfo(port_info);
    port_info = NULL;

    if (listen(listen_socket, 5) != 0) {
        perror("listen");
        goto mbs_err_exit;
    }

    return listen_socket;

mbs_err_exit:
    freeaddrinfo(port_info);
    close(listen_socket);
    return -1;
}

struct List{
    int fd;
    struct List *next;
};


int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: server PORT\n");
        return 1;
    }

    int listen_socket = make_bound_socket(argv[1]);
    if (listen_socket < 0) {
        return 1;
    }

    struct List *mylist = 0;
    int users_online = 0;

    while (1) {

        fd_set read_fds;
        FD_ZERO(&read_fds);

        FD_SET(listen_socket, &read_fds);

        struct List *current = mylist;

        int max = listen_socket;
        while(current != NULL) {
            FD_SET(current->fd, &read_fds);
            if (max < current->fd) {
                max = current->fd;
            }
            current = current->next;
        }

        if (select(max + 1, &read_fds, NULL, NULL, NULL) > 0) {
            if (FD_ISSET(listen_socket, &read_fds)) {
                int client_fd = accept(listen_socket, NULL, NULL);
                if (client_fd < 0) return 1;

                users_online++;
                char greeting[100];
                int greeting_length = sprintf(greeting, "%d user%s online\n",
                        users_online, users_online > 1 ? "s" : "");
                write(client_fd, greeting, greeting_length);

                struct List *temp_list = calloc(1, sizeof(struct List));
                temp_list->fd = client_fd;
                temp_list->next = mylist;
                mylist = temp_list;
            }
            struct List **current = &mylist;
            while(*current != NULL) {
                if (FD_ISSET((*current)->fd, &read_fds)) {
                    char buf[1024];
                    int was_read = read((*current)->fd, buf, sizeof(buf));
                    if (was_read == 0) {
                        close((*current)->fd);
                        struct List* next = (*current)->next;
                        free(*current);
                        *current = next;
                        users_online--;
                        if (!next)
                            break;
                    } else if (was_read < 0) {
                        perror("read");
                        return 1;
                    } else {
                        struct List *write_client = mylist;
                        while (write_client != NULL) {
                            if (write_client->fd != (*current)->fd) {
                                write(write_client->fd, buf, was_read);
                            }
                            write_client = write_client->next;
                        }
                    }
                }
                current = &((*current)->next);
            }
        }
    }

    return 0;
}
