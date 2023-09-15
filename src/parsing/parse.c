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
	return (check_map(map, map_size));
}

int	get_map(t_map **map, char *line, int fd)
{
	t_lst	*lst;

	if (!line)
		return (printf("Error: No map.\n"), EXIT_FAILURE);
	lst = NULL;
	while (line)
	{
		if (is_line_for_map(line) == EXIT_FAILURE
			|| lst_add_back(&lst, line) == EXIT_FAILURE)
			return (free(line), free_lst(&lst), EXIT_FAILURE);
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	if (!lst)
		return (printf("Error: No map.\n"), free(line), EXIT_FAILURE);
	if (lst_size(lst) <= 1)
		return (printf("Error: Invalid map.\n"), EXIT_FAILURE);
	(*map)->map = create_map(lst, &((*map)->map_size));
	if (!(*map)->map)
		return (free(line), free_lst(&lst), EXIT_FAILURE);
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

t_map	*parse_map(t_map *map, int fd, char *line)
{
	if (empty_params(map))
	{
		if (line)
			free(line);
		return (printf("Error: Missing params.\n"), free_map(map),
			close(fd), NULL);
	}
	if (get_map(&map, ignore_empty_lines(line, fd), fd) == EXIT_FAILURE)
		return (close(fd), free_map(map), NULL);
	if (check_player(map) == EXIT_FAILURE)
		return (free_map(map), close(fd), NULL);
	return (close(fd), map);
}

t_map	*parse(char *path)
{
	char	*line;
	int		fd;
	t_map	*map;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = init_map();
	if (!map)
		return (close(fd), NULL);
	line = get_next_line(fd);
	if (!line)
		return (close(fd), free_map(map), NULL);
	while (line && empty_params(map))
	{
		if (get_param(&map, line) == EXIT_FAILURE)
			return (free_map(map), free(line), close(fd), NULL);
		free(line);
		line = get_next_line(fd);
	}
	return (parse_map(map, fd, line));
}
