#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

int main(int args, char *argv[]) {
    char node[1001];
    char service[1001];
    while (scanf("%1000s %1000s", node, service) == 2) {

        struct addrinfo hints = {};
        hints.ai_family = AF_INET;
        struct addrinfo *res;

        int retValue;
        if ((retValue = getaddrinfo(node, service, &hints, &res)) != 0) {
            printf("%s\n", gai_strerror(retValue));
        } else {
            if (res) {
                printf("%s:%u\n", 
                       inet_ntoa(((struct sockaddr_in*) res->ai_addr)->sin_addr),
                       ntohs(((struct sockaddr_in*) res->ai_addr)->sin_port));
            }
            freeaddrinfo(res);
        }
 
    }

}
