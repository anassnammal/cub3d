/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_vec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anammal <anammal@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:31:50 by anammal           #+#    #+#             */
/*   Updated: 2024/03/13 13:46:38 by anammal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vector	cub_vec(double x, double y)
{
	t_vector	v;

	v.x = x;
	v.y = y;
	return (v);
}

t_vector	cub_vec_add(t_vector a, t_vector b)
{
	return (
		cub_vec(a.x + b.x, a.y + b.y)
	);
}

t_vector	cub_vec_mul(t_vector a, double b)
{
	return (
		cub_vec(a.x * b, a.y * b)
	);
}

t_vector	cub_vec_rot(t_vector a, double angle)
{
	return (
		cub_vec(a.x * cos(angle) - a.y * sin(angle),
			a.x * sin(angle) + a.y * cos(angle))
	);
}
