#include "cub3d.h"

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

void	*cub_get(void)
{
	static t_scene	data;

	return (&data);
}

t_ui8   loadxpm(void *mlx, void **img, char *xpm, t_ui8 type)
{
	int     w;
	int     h;

	*img = mlx_xpm_file_to_image(mlx, xpm, &w, &h);
	// if (!*img)
	// 	return (ft_putendl_fd("ERROR: invalid xpm file", 1), ERROR);
	return (type);
}

t_ui8   loadrgb(t_rgb *ptr, char *s, t_ui8 type)
{   
	short	tmp;    
	short	c;

	*ptr = 0;
	c = 3;
	while (*s && c--)
	{
		tmp = 0;
        while (ft_isdigit(*s) && tmp <= 0xFF)
            tmp = tmp * 10 + (*s++ - 48);
        if (tmp > 0xFF)
            return (ERROR);
		*ptr |= tmp << c * 8;
		s += (*s == ',' && c != 0);
	}
	if (*s || c != 0)
		return (ERROR);
	return (type);
}

t_ui8   load_setting(char *s, t_ui8 type)
{
    t_scene *data;

    data = cub_get();
    if (type == NORTH)
        type = loadxpm(data->mlx, &data->imgs.no, s, type);
    else if (type == SOUTH)
        type = loadxpm(data->mlx, &data->imgs.so, s, type);
    else if (type == WEST)
        type = loadxpm(data->mlx, &data->imgs.we, s, type);
    else if (type == EAST)
        type = loadxpm(data->mlx, &data->imgs.ea, s, type);
    else if (type == FLOOR)
        type = loadrgb(&data->floor, s, type);
    else if (type == CEILING)
        type = loadrgb(&data->ceiling, s, type);
    else
        type = ERROR;
    return (type);
}

t_ui8   get_type(char **s)
{
    if (!**s)
        return (EMPTY);
    else if (!ft_strncmp(*s, "NO ", 3))
        return (((*s) += 2), NORTH);
    else if (!ft_strncmp(*s, "SO ", 3))
        return (((*s) += 2), SOUTH);
    else if (!ft_strncmp(*s, "WE ", 3))
        return (((*s) += 2), WEST);
    else if (!ft_strncmp(*s, "EA ", 3))
        return (((*s) += 2), EAST);
    else if (!ft_strncmp(*s, "F ", 2))
        return (((*s) += 1), FLOOR);
    else if (!ft_strncmp(*s, "C ", 2))
        return (((*s) += 1), CEILING);
    return (ERROR);
}

t_ui8	scan_line(char **s)
{
    t_ui8   type;
	size_t	i;

	i = 0;
	while (ft_isspace(**s))
		*(*s)++ = 0;
    type = get_type(s);
    while (ft_isspace(**s))
		*(*s)++ = 0;
    while (s[0][i] && !ft_isspace(s[0][i]))
        i++;
    while (ft_isspace(s[0][i]))
        s[0][i++] = 0;
    if ((type && i == 0) || s[0][i])
        return (ERROR);
    return (type);
}

t_ui8   parse_setting(char *s, t_ui8 state)
{
    t_ui8   type;

    if (!s)
        return (ERROR);
    type = scan_line(&s);
    if (state & type)
        return (ERROR);
    if (!type || type & ERROR)
        return (type);
    return (load_setting(s, type));
}

int     isempty(char *s)
{
    while (ft_isspace(*s))
        s++;
    return (!*s);
}

t_ui8   add_node(t_list **list, char *line)
{
    t_list  *new;

    if (isempty(line))
    {
        if (*list)
            return (free(line), MAP);
        return (free(line), EMPTY);
    }
    new = ft_lstnew(line);
    if (!new)
        return (free(line), ERROR);
    ft_lstadd_back(list, new);
    return (EMPTY);
}

void    copy_map_line(char *dest, char *src)
{
    while (*src)
    {
        if (ft_isspace(*src))
            *dest = 0;
        else
            *dest = *src;
        src++;
        dest++;
    }
}

t_ui8   export(t_map *map, t_list *list)
{
    int i;

    map->content = ft_calloc(map->y_max, sizeof(char *));
    if (!map->content)
        return (ERROR);
    i = 0;
    while (list)
    {
        map->content[i] = ft_calloc(map->x_max, sizeof(char));
        if (!map->content[i])
            return (ft_free2d((void **)map->content), ERROR);
        copy_map_line(map->content[i], list->content);
        list = list->next;
        i++;
    }
    return (MAP);
}

t_ui8   check_line(t_map *map, size_t x, size_t y)
{
    if (ft_memchr("NSWE", map->content[y][x], 4))
    {
        if (map->y_player || map->x_player)
            return (ERROR);
        map->x_player = x;
        map->y_player = y;
    }
    else if (!ft_memchr("10", map->content[y][x], 3))
        return (ERROR);
    if ((map->content[y][x] != 0
        && map->content[y][x] != 49
        && (x == 0 || x == map->x_max - 1
        || y == 0 || map->y_max - 1 == y
        || map->content[y + 1][x] == 0
        || map->content[y - 1][x] == 0
        || map->content[y][x + 1] == 0
        || map->content[y][x - 1] == 0)))
        return (ERROR);
    return (MAP);
}

t_ui8   validate(t_map *map)
{
    size_t  x;
    size_t  y;

    y = 0;
    while (y < map->y_max)
    {
        x = 0;
        while (x < map->x_max)
        {
            if (check_line(map, x, y) & ERROR)
                return (MAP | ERROR);
            x++;
        }
        y++;
    }
    if (!map->x_player)
        return (MAP | ERROR);
    return (MAP);
}

t_ui8   loadmap(t_list *list)
{
    t_scene *data;
    t_list *tmp;
    size_t  x;
    size_t  y;

    data = cub_get();
    y = 0;
    tmp = list;
    while (tmp)
    {
        x = ft_strlen((char *)tmp->content);
        if (data->map.x_max < x)
           data->map.x_max = x;
        tmp = tmp->next;
        y++;
    }
    data->map.y_max = y;
    if (export(&data->map, list) & ERROR)
        return (ft_lstclear(&list, free), ERROR);
    ft_lstclear(&list, free);
    return (validate(&data->map));
}

t_ui8   load_scene(int file)
{
    char    *line;
    t_list  *list;
    t_ui8   scene;

    scene = 0;
    while (scene < 0x3F)
    {
        line = get_next_line(file);
        scene |= parse_setting(line, scene);
        free(line);
    }
    list = NULL;
    while ((line = get_next_line(file)) && scene < MAP)
        scene |= add_node(&list, line);
    scene &= ~MAP;
    while (line && isempty(line))
        (free(line), line = get_next_line(file));
    if (scene & ERROR || line || !list)
        return (ft_lstclear(&list, free) ,free(line), scene | ERROR);
    return ((scene |= loadmap(list)));
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
        exit(1);
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