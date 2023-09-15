#include "cub3d.h"

int	empty_params(t_map *map)
{
	if (!map->no || !map->so || !map->we || !map->ea)
		return (1);
	if (map->f.r == -1 || map->f.g == -1 || map->f.b == -1)
		return (1);
	if (map->c.r == -1 || map->c.g == -1 || map->c.b == -1)
		return (1);
	return (0);
}

char	**check_map(char **map, t_vec2 *map_size)
{
	if (map_size->x == 0 || map_size->x == 1
		|| !space_extension(map, map_size->x))
		return (printf("Error: Invalid map.\n"), NULL);
	if (check_isolation(map, map_size->y) == EXIT_FAILURE)
		return (printf("Error: Map is not closed.\n"), free_tab(map), NULL);
	return (map);
}

int	is_line_for_map(char *line)
{
	int	i;

	i = 0;
	if (empty_line(line))
		return (printf("Error : Line for map is empty\n"), EXIT_FAILURE);
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != '2'
			&& line[i] != 'N' && line[i] != 'S' && line[i] != 'E'
			&& line[i] != 'W' && line[i] != ' ')
			return (printf("Error : invalid character in map\n"), EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

void	find_dir(t_map **map, char *line, int *res, int i)
{
	if (!ft_strncmp(line + i, "NO", 2) && line[i + 2] == ' ')
		*res = put_dir(&((*map)->no), line + i + 2);
	else if (!ft_strncmp(line + i, "SO", 2) && line[i + 2] == ' ')
		*res = put_dir(&((*map)->so), line + i + 2);
	else if (!ft_strncmp(line + i, "WE", 2) && line[i + 2] == ' ')
		*res = put_dir(&((*map)->we), line + i + 2);
	else if (!ft_strncmp(line + i, "EA", 2) && line[i + 2] == ' ')
		*res = put_dir(&((*map)->ea), line + i + 2);
	else if (!ft_strncmp(line + i, "F", 1) && line[i + 1] == ' ')
		*res = put_color(&((*map)->f), line + i + 1);
	else if (!ft_strncmp(line + i, "C", 1) && line[i + 1] == ' ')
		*res = put_color(&((*map)->c), line + i + 1);
}
