#ifndef PROTOTYPE_H
#define PROTOTYPE_H

#include "./engine.h"
// Vector Operations
t_vector    vec_add(t_vector a, t_vector b);
t_vector    vec_sub(t_vector a, t_vector b);
t_vector    vec_mult(t_vector a, double b);
t_vector    vec_rotate(t_vector a, double angle);
double      vec_dot(t_vector a, t_vector b);
t_vector    vec_norm(t_vector a);


#endif // PROTOTYPE_H