#include "cub3d.h"

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
	if (s[0][i] && i == 0)
		return (ERROR);
	return (type);
}

t_ui8   load_image(char *s)
{
    t_ui8   type;

    if (s)
        return (ERROR);
    type = scan_line();

	return (type);
}

t_ui8   load_settings(int file)
{
    char    *line;
    t_ui8   scene;

    while (scene < 0x3F)
    {
        line = get_next_line(file);
        scene |= load_image(line);
        scene |= load_color(line);
        free(line);
    }
    return (scene);
}

int		load_scene(int file)
{
	t_ui8   scene;

    scene = 0;
    scene |= load_settings(file);
    if (scene == ERROR)
        return (scene & ~MAP);
    scene |= load_map(file);
    if (scene == ERROR)
        return (scene);
    close(file);
    return (scene);
}