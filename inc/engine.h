#ifndef ENGINE_H
#define ENGINE_H

#include <math.h>
#include <stdbool.h>

typedef struct s_vector{
    double x;
    double y;
}t_vector;

typedef struct s_vecstack{
    t_vector *vec;
    t_vector strich;
    t_vector first_inter;
}t_vecstack;

typedef struct s_img{
    void *ptr;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
}t_img;

#endif // ENGINE_H