#include "cub3d.h"

t_vector    cub_vec(int x, int y)
{
    t_vector	v;

    v.x = x;
    v.y = y;
    return (v);
}

t_vector    cub_vec_add(t_vector a, t_vector b)
{
    return (cub_vec(a.x + b.x, a.y + b.y));
}

t_vector    cub_vec_sub(t_vector a, t_vector b)
{
    return (cub_vec(a.x - b.x, a.y - b.y));
}

t_vector    cub_vec_mul(t_vector a, int b)
{
    return (cub_vec(a.x * b, a.y * b));
}

t_vector    cub_vec_div(t_vector a, int b)
{
    return (cub_vec(a.x / b, a.y / b));
}

uint32_t    cub_vec_dot(t_vector a, t_vector b)
{
    return (a.x * b.x + a.y * b.y);
}

uint32_t    cub_vec_cross(t_vector a, t_vector b)
{
    return (a.x * b.y - a.y * b.x);
}

uint32_t    cub_vec_len(t_vector a)
{
    return (sqrt(cub_vec_dot(a, a)));
}

t_vector    cub_vec_norm(t_vector a)
{
    return (cub_vec_div(a, cub_vec_len(a)));
}

t_vector    cub_vec_rot(t_vector a, int angle)
{
    return (cub_vec(a.x * cos(angle) - a.y * sin(angle), a.x * sin(angle) + a.y * cos(angle)));
}
