#ifndef ARRAY_FUNCS_H
#define ARRAY_FUNCS_H

typedef struct
{
    char *title;
    char *name;
    int year;
} movie_t;

int allocate_movies(movie_t **movies, int movies_count);
void print_movies_array(movie_t *movies, size_t len);
void print_movie(const movie_t *movie);
void free_movie(movie_t movie);
void free_movies(movie_t *movies, size_t count);

int bin_search_by_key(movie_t *movies, size_t len, char *key, char *field, int *ind);
int bin_search_title(movie_t *movies, size_t len, char *key);
int bin_search_name(movie_t *movies, size_t len, char *key);
int bin_search_year(movie_t *movies, size_t len, int key);

#endif//ARRAY_FUNCS_H
