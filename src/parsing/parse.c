#include "cub3d.h"

char	**create_map(t_lst *lst, t_vec2 *map_size)
{
	char	**map;
	int		i;
	t_lst	*tmp;

	i = 0;
	tmp = lst;
	map_size->y = lst_size(lst);
	map_size->x = 0;
	map = malloc(sizeof(char *) * (map_size->y + 1));
	if (!map)
		return (printf("Error: Malloc error for map.\n"), NULL);
	while (tmp)
	{
		if (map_size->x < tmp->size)
			map_size->x = tmp->size;
		map[i] = ft_strdup(tmp->tab);
		if (!map[i])
			return (printf("Error: Strdup failed.\n"), free_tab(map), NULL);
		i++;
		tmp = tmp->next;
	}
	map[i] = NULL;
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
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	get_map(t_map **map, char *line, int fd)
{
	t_map	*tmp;
	t_lst	*lst;

	if (!line)
		return (printf("Error: No map.\n"), EXIT_FAILURE);
	tmp = *map;
	lst = NULL;
	while (line)
	{
		if (is_line_for_map(line) == EXIT_FAILURE
			|| lst_add_back(&lst, line) == EXIT_FAILURE)
			return (free_lst(&lst), free(line), EXIT_FAILURE);
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	if (!lst)
		return (printf("Error: No map.\n"), free(line), EXIT_FAILURE);
	if (lst_size(lst) <= 1)
		return (printf("Error: Invalid map.\n"), EXIT_FAILURE);
	tmp->map = create_map(lst, &(tmp->map_size));
	if (!tmp->map)
		return (free_lst(&lst), EXIT_FAILURE);
	return (free_lst(&lst), EXIT_SUCCESS);
}

t_map	*init_map(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (printf("Error: Malloc error for map.\n"), NULL);
	map->no = NULL;
	map->so = NULL;
	map->we = NULL;
	map->ea = NULL;
	init_color(&(map->f));
	init_color(&(map->c));
	map->map = NULL;
	return (map);
}

t_map	*parse(char *path)
{
	char	*line;
	int		fd;
	t_map	*map;

	fd = open(path, O_RDONLY);
	map = init_map();
	line = get_next_line(fd);
	if (!map || fd < 0 || !line)
		return (NULL);
	while (line && empty_params(map))
	{
		if (get_param(&map, line) == EXIT_FAILURE)
			return (free_map(map), free(line), NULL);
		free(line);
		line = get_next_line(fd);
	}
	if (empty_params(map))
		return (printf("Error: Missing params.\n"), free_map(map),
			free(line), NULL);
	if (get_map(&map, ignore_empty_lines(line, fd), fd) == EXIT_FAILURE)
		return (free_map(map), NULL);
	if (check_player(map) == EXIT_FAILURE)
		return (free_map(map), NULL);
	return (map);
}
