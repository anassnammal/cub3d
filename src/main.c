/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anammal <anammal@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 05:40:17 by anammal           #+#    #+#             */
/*   Updated: 2024/01/07 06:32:57 by anammal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_file(char const *s)
{
	int		fd;
	char	*start;

	start = ft_strrchr(s, '.');
	if (!start || s == start || ft_strncmp(start, ".cub", 5))
		(printf("ERROR: ./cub3d *.cub"), exit(EXIT_FAILURE));
	fd = open(s, O_RDONLY);
	if (fd == -1)
		(perror("ERROR"), exit(EXIT_FAILURE));
	return (fd);
}

void	*cub_get(void)
{
	static t_scene	data;

	return (&data);
}

void	cub_exit(t_ui8 scene)
{
	t_scene	*data;

	data = cub_get();	
	if (scene == NORTH)
		mlx_destroy_image(data->mlx, data->imgs.no);
	else if (scene == SOUTH)
		mlx_destroy_image(data->mlx, data->imgs.so);
	else if (scene == WEST)
		mlx_destroy_image(data->mlx, data->imgs.we);
	else if (scene == EAST)
		mlx_destroy_image(data->mlx, data->imgs.ea);
	else if (scene == MAP)
	{
		ft_free2d(data->map.content);
		mlx_destroy_window(data->mlx, data->win);
	}
}

int main(int ac, char const **av)
{
	int		file;
	t_ui8   scene;
	if (ac != 2)
		exit(EXIT_FAILURE);
	file = check_file(av[1]);
	t_scene *data = cub_get();
	// data->mlx = mlx_init();
	scene = load_scene(file);
	close(file);
	printf("status %d\n", scene);
	if (scene & ERROR)
		cub_exit(scene);
	// data->win = mlx_new_window(data->mlx, data->map.x_max * 32, data->map.y_max * 32, "cub3d");
	t_ui8    *f = (t_ui8 *)&(data->floor);
	t_ui8    *c = (t_ui8 *)&(data->ceiling);
	printf("%d,%d,%d,%d\n", f[3], f[2], f[1], f[0]);
	printf("%d,%d,%d,%d\n", c[3], c[2], c[1], c[0]);
	for (size_t i = 0; i < data->map.y_max; i++)
	{
		for (size_t j = 0; j < data->map.x_max; j++)
		{
			if (data->map.content[i][j])
				printf("%c", data->map.content[i][j]);
			else
				printf(" ");
		}
		printf("\n"); 
	}
	return 0;
}
