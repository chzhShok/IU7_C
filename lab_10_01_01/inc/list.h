#ifndef LIST_H
#define LIST_H

#include <stdio.h>

typedef struct
{
    char *name;
    int year;
    double rating;
} film_t;

typedef struct node_t node_t;

struct node_t
{
    void *data;
    node_t *next;
};

node_t *create_node(void *data);
int push_back(node_t **head, void *data);
int read_data(FILE *f, node_t **head);
void fprint_list(FILE *f, node_t *head);
void free_list(node_t *head);

void *pop_front(node_t **head);
void *pop_back(node_t **head);
int copy(node_t *head, node_t **new_head);
int comparator(const void *el1, const void *el2);
node_t *sort(node_t *head, int (*comparator)(const void *, const void *));

#endif//LIST_H
