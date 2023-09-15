#include "cub3d.h"

void	init_color(t_color *color)
{
	color->r = -1;
	color->g = -1;
	color->b = -1;
}

int	empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

char	*ignore_empty_lines(char *line, int fd)
{
	while (line && empty_line(line))
	{
		free(line);
		line = get_next_line(fd);
	}
	if (!line)
		return (printf("Error: No map.\n"), NULL);
	return (line);
}

int	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
	return (EXIT_SUCCESS);
}

int	free_map(t_map *map)
{
	if (map)
	{
		if (map->no)
			free(map->no);
		if (map->so)
			free(map->so);
		if (map->we)
			free(map->we);
		if (map->ea)
			free(map->ea);
		if (map->map)
			free_tab(map->map);
		free(map);
	}
	return (EXIT_SUCCESS);
}
