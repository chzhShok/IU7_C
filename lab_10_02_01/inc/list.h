#ifndef LIST_H
#define LIST_H

typedef struct node_t node_t;

struct node_t
{
    int degree;
    int coeff;
    node_t *next;
};

node_t *create_node(int degree, int coeff);
void free_list(node_t *node);
void print_polynomial(const node_t *head);

int read_polynomial(node_t **head);
int calculate_val(node_t **head, int val);

int derivative(node_t **head, node_t **d_head);

node_t *sum_polynomials(node_t **head1, node_t **head2);

int odd_even_polynomial(node_t **head, node_t **even, node_t **odd);

#endif//LIST_H
