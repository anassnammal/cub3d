#include "cub3d.h"

void	*cub_get(void)
{
	static t_scene	data;

	return (&data);
}

t_rgb	getrgb(char *s)
{
	t_rgb	color;    
	short	tmp;    
	short	c;

	color = 0;
	c = 3;
	while (c--)
	{
		if (!*s)
			return (-1);
		tmp = 0;
		while (ft_isdigit(*s) && tmp <= 0xFF)
			tmp *= 10 + (*s++ - 48);
		color |= tmp << c * 8;
		s += (*s == ',');
	}
	if (*s)
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
		return (ft_putendl_fd("ERROR: invalid xpm file", 1), NULL);
	return (ptr);
}

int		cub_set(char *type, char *val)
{
	t_scene	*d;
	int		w;
	int		h;

	d = cub_get();
	if (!d->imgs.no && !ft_strncmp(type, "NO", 3))
		return (d->imgs.no = load_xpm(d->mlx, val));
	else if (!d->imgs.so && !ft_strncmp(type, "SO", 3))
		return (d->imgs.so = load_xpm(d->mlx, val));
	else if (!d->imgs.we && !ft_strncmp(type, "WE", 3))
		return (d->imgs.we = load_xpm(d->mlx, val));
	else if (!d->imgs.ea && !ft_strncmp(type, "EA", 3))
		return (d->imgs.ea = load_xpm(d->mlx, val));
	else if (!d->ceiling && !ft_strncmp(type, "C", 2))
		return ((d->ceiling = setrgb(val)) != 0xFFFFFFFF);
	else if (!d->floor && !ft_strncmp(type, "F", 2))
		return ((d->floor = setrgb(val)) != 0xFFFFFFFF);
	return (0);
}

int		scan_line(char *s, size_t pos[2])
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (j < 2)
	{
		if (!ft_isspace(s[i]))
			pos[j++] = i;
		while (s[i] && !ft_isspace(s[i]))
			i++;
		while (ft_isspace(s[i]))
			s[i++] = 0;
	}
	if (s[i] || i == pos[1])
		return(0);
	return (1);
}

int		check_file(char const *s)
{
	int 	fd;
	char	*start;

	start = ft_strrchr(s, '.');
	if (!start || s == start || ft_strncmp(start, ".cub", 5))
		(printf("ERROR: ./cub3d *.cub"), exit(EXIT_FAILURE));
	fd = open(s, O_RDONLY);
	if (fd == -1)
		(perror("ERROR"), exit(EXIT_FAILURE));
	return (fd);
}

int		parser(int file)
{
	char	*line;
	int 	c;

	c = 0;
	while ((line = get_next_line(file)))
	{
		;
	}
	return c;



}

int main(int ac, char const **av)
{
	int	file;

	if (ac != 2)
		exit(EXIT_FAILURE);
	file = check_file(av[1]);
	parser(file);
	return 0;
}