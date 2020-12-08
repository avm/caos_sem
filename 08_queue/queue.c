#include <stdlib.h>
#include <stdio.h>
#include <string.h>


struct node {
    int id;
    struct node *next;
    struct node *prev;
};


struct node* add_new_node(struct node *head, int id) {
    if (head == NULL) {
        head = calloc(sizeof(*head), 1);
        head->id = id;
        head->next = head;
        head->prev = head;
        return head;
    }
    struct node* new_node = calloc(sizeof(*head), 1);
    new_node->id = id;
    new_node->next = head;
    new_node->prev = head->prev;
    head->prev->next = new_node;
    head->prev = new_node;
    return head;
}

struct node* process_node(struct node* head) {
    if (head == NULL) {
        printf("List is empty!!!\n");
        return NULL;
    }
    printf("%i\n", head->id);
    if (head->next == head) {
        free(head);
        return NULL;
    }
    head->next->prev = head->prev;
    head->prev->next = head->next;
    struct node *new_head = head->next;
    free(head);
    return new_head;
}

struct node* move_to_back(struct node* head) {
    if (!head) {
        printf("List is empty!!\n");
        return NULL;
    } 
    return head->next;
}

int main(void) {
    struct node *head = NULL;
    char cmd[20];

    while (scanf("%19s", cmd) == 1) {
        if (!strcmp(cmd, "add")) {
            int id;
            if (scanf("%d", &id) != 1) {
                fprintf(stderr, "No id provided\n");
                continue;
            }
            head = add_new_node(head, id);
        } else if (!strcmp(cmd, "process")) {
            head = process_node(head);
        } else if (!strcmp(cmd, "mtb")) {
            head = move_to_back(head);
        } else {
            printf("Unknown command: %s\n", cmd);
        }
    }
    return 0;
}
