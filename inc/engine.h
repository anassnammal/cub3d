#ifndef ENGINE_H
#define ENGINE_H

#include <math.h>
#include <stdbool.h>
#include "./prototype.h"
#include "./struct.h"

#define SCALE 100

typedef struct s_vector{
    double x;
    double y;
}t_vector;

typedef struct s_player{
    int move;
    t_vector dir;
    t_vector pos;
}t_player;

#endif // ENGINE_H