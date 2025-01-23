#ifndef COMMON_FUNCS_H
#define COMMON_FUNCS_H

int str_to_int(char *s, int *num);
int get_command(int argc, char **argv);
int preprocess_arg(char *src, char **dst, int len);

#endif//COMMON_FUNCS_H
