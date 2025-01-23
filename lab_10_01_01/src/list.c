#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "list.h"

#define _GNU_SOURCE

node_t *create_node(void *data)
{
    node_t *new_node = (node_t *) malloc(sizeof(node_t));
    if (new_node == NULL)
        return NULL;

    new_node->data = data;
    new_node->next = NULL;

    return new_node;
}

int push_back(node_t **head, void *data)
{
    node_t *new_node = create_node(data);
    if (new_node == NULL)
        return ENOMEM;

    if (*head == NULL)
    {
        *head = new_node;
    }
    else
    {
        node_t *tmp = *head;
        while (tmp->next)
            tmp = tmp->next;

        tmp->next = new_node;
    }

    return 0;
}

int read_lines(FILE *f, char **name, size_t *linecap_name, char **year, size_t *linecap_year, char **rating, size_t *linecap_rating)
{
    return getline(name, linecap_name, f) > 0 && getline(year, linecap_year, f) > 0 && getline(rating, linecap_rating, f) > 0;
}

int read_data(FILE *f, node_t **head)
{
    char *name = NULL, *year = NULL, *rating = NULL;
    size_t linecap_name = 0, linecap_year = 0, linecap_rating = 0;

    while (read_lines(f, &name, &linecap_name, &year, &linecap_year, &rating, &linecap_rating))
    {
        film_t *new_film = (film_t *) malloc(sizeof(film_t));
        if (!new_film)
            return ENOMEM;

        name[strcspn(name, "\n")] = '\0';
        year[strcspn(year, "\n")] = '\0';
        rating[strcspn(rating, "\n")] = '\0';

        new_film->name = malloc(sizeof(char) * (strlen(name) + 1));
        if (!new_film->name)
        {
            free(new_film);
            return ENOMEM;
        }
        strcpy(new_film->name, name);

        char *endptr = NULL;
        int year_int = (int) strtol(year, &endptr, 10);
        if (endptr == year || (*endptr != '\n' && *endptr != '\0'))
        {
            free(new_film->name);
            free(new_film);
            return EIO;
        }

        double rating_double = strtod(rating, &endptr);
        if (endptr == rating || (*endptr != '\n' && *endptr != '\0'))
        {
            free(new_film->name);
            free(new_film);
            return EIO;
        }

        new_film->year = year_int;
        new_film->rating = rating_double;

        int rc = push_back(head, (void *) new_film);
        if (rc != 0)
        {
            free(new_film->name);
            free(new_film);
            return rc;
        }
    }

    free(name);
    free(year);
    free(rating);

    return 0;
}

void *pop_front(node_t **head)
{
    if (!head || !(*head))
        return NULL;

    void *data = (*head)->data;
    node_t *tmp = *head;

    *head = (*head)->next;
    free(tmp);

    return data;
}

void *pop_back(node_t **head)
{
    if (!head || !(*head))
        return NULL;

    void *data;

    if ((*head)->next == NULL)
    {
        data = (*head)->data;
        free(*head);
        *head = NULL;
        return data;
    }

    node_t *prev = NULL;
    node_t *cur = *head;

    while (cur->next)
    {
        prev = cur;
        cur = cur->next;
    }

    data = cur->data;
    free(cur);

    prev->next = NULL;

    return data;
}

void free_list(node_t *head)
{
    while (head != NULL)
    {
        node_t *temp = head;
        head = head->next;
        free(temp);
    }
}

int copy(node_t *head, node_t **new_head)
{
    if (new_head == NULL)
        return EINVAL;

    *new_head = NULL;

    if (head == NULL)
        return EINVAL;

    for (node_t *current = head; current != NULL; current = current->next)
    {
        int rc = push_back(new_head, current->data);
        if (rc != 0)
            return rc;
    }

    return 0;
}

int comparator(const void *el1, const void *el2)
{
    film_t *film1 = (film_t *) el1;
    film_t *film2 = (film_t *) el2;

    return film1->year - film2->year;
}

void sorted_insert(node_t **head, node_t *element, int (*comparator)(const void *, const void *))
{
    if (*head == NULL || comparator(element->data, (*head)->data) < 0)
    {
        element->next = *head;
        *head = element;
        return;
    }

    node_t *prev = NULL;
    node_t *cur = *head;
    while (cur && comparator(element->data, cur->data) >= 0)
    {
        prev = cur;
        cur = cur->next;
    }

    prev->next = element;
    element->next = cur;
}

node_t *sort(node_t *head, int (*comparator)(const void *, const void *))
{
    if (head == NULL || head->next == NULL)
        return head;

    node_t *sorted = NULL;

    while (head)
    {
        node_t *next = head->next;
        head->next = NULL;
        sorted_insert(&sorted, head, comparator);
        head = next;
    }

    return sorted;
}

static void fprint_film(FILE *f, char *name, int year, double rating)
{
    fprintf(f, "%s\n%d\n%.1f\n", name, year, rating);
}

void fprint_list(FILE *f, node_t *head)
{
    node_t *tmp = head;
    while (tmp)
    {
        film_t *film = (film_t *) tmp->data;
        fprint_film(f, film->name, film->year, film->rating);
        tmp = tmp->next;
    }
}
