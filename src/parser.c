#include "cub3d.h"

void	*cub_get(void)
{
	static t_scene	data;

	return (&data);
}

unsigned int	setrgb(char *s)
{
	unsigned int	color;    
	unsigned int	tmp;    
	int				c;

	color = 0;
	c = 3;
	while (c--)
	{
		tmp = 0;
		while (ft_isdigit(*s))
		{
			tmp *= 10 + (*s - 48);
			s++;
		}
		if (tmp > 255)
			return (-1);
		color |= tmp << (8 * c);
		s += (*s == ',');
	}
	if (!*s || c != -1)
		return (-1);
	return (color);
}

void	*loadxpm(void *mlx, char *file)
{
	int     w;
	int     h;
	void    *ptr;

	ptr = mlx_xpm_file_to_image(mlx, file, &w, &h);
	if (!ptr)
		(ft_putendl_fd("ERROR: invalid xpm file", 1), exit(1));
	return (ptr);
}

int cub_set(int t, int v, char *s)
{
	t_scene	*d;
	int		w;
	int		h;

	d = cub_get();
	if (!d->imgs.no && !ft_strncmp(s + t, "NO", 3))
		return (d->imgs.no = load_xpm(d->mlx, s + v));
	else if (!d->imgs.so && !ft_strncmp(s + t, "SO", 3))
		return (d->imgs.so = load_xpm(d->mlx, s + v));
	else if (!d->imgs.we && !ft_strncmp(s + t, "WE", 3))
		return (d->imgs.we = load_xpm(d->mlx, s + v));
	else if (!d->imgs.ea && !ft_strncmp(s + t, "EA", 3))
		return (d->imgs.ea = load_xpm(d->mlx, s + v));
	else if (!d->color.ceiling && !ft_strncmp(s + t, "C", 2))
		return ((d->color.ceiling = setrgb(s + v)) != 0xFFFFFFFF);
	else if (!d->color.ceiling && !ft_strncmp(s + t, "F", 2))
		return ((d->color.ceiling = setrgb(s + v)) != 0xFFFFFFFF);
	return (0);
}
