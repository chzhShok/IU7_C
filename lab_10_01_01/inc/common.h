#ifndef COMMON_H
#define COMMON_H

#include "list.h"
#include "error.h"

int process_operation(char *operation, node_t **head);
int process_error(int rc);

#endif//COMMON_H
