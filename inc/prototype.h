#ifndef PROTOTYPE_H
#define PROTOTYPE_H

#include "./engine.h"

t_vector v_add(t_vector v1, t_vector v2);
t_vector v_multi(t_vector v1, t_vector v2);
t_vector v_rot(t_vector v, double angle);
t_vector v_sub(t_vector v1, t_vector v2);
double v_dot(t_vector v1, t_vector v2);
t_vector v_norm(t_vector v);
#endif // PROTOTYPE_H