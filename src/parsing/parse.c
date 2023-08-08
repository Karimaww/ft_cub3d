#include "cub3d.h"



int	get_param(t_map **map, char *line)
{
	t_map	*tmp;
	int		i;

	tmp = *map;
	i  = 0;
	while (line[i])
	{
		if (!ft_strncmp(line + i, "NO", 3))
			put_dir(tmp->no, line + i + 2);
		else if (!ft_strncmp(line + i, "SO", 3))
			put_dir(tmp->so, line + i + 2);
		else if (!ft_strncmp(line + i, "WE", 3))
			put_dir(tmp->we, line + i + 2);
		else if (!ft_strncmp(line + i, "EA", 3))
			put_dir(tmp->ea, line + i + 2);
		
		i++;
	}
	return (EXIT_SUCCESS);
}

t_map	

int	parse(char *path)
{
	char	*line;
	int		fd;
	t_map	*map;

	fd = open(path, O_RDONLY);
	map = malloc(sizeof(map));
	line = get_next_line(fd);
	if (!map || fd < 0 || !line)
		return (EXIT_FAILURE);
	while (line && (!map->no || !map->so || !map->we || !map->ea
		|| !map->f || !map->c))
	{
		if (get_param(&map, line) == EXIT_FAILURE)
			return (free_map(map), free(line), EXIT_FAILURE);
		free(line);
		line = get_next_line(fd);
	}
	get_map(&map, fd);
	return (EXIT_SUCCESS);
}

int main(int ac, char **av, char **env)
{
	if (!*env)
		return (write(2, "Error\n", 6), EXIT_FAILURE);
	if (ac != 2)
		return (write(2, "Error\n", 6), EXIT_FAILURE);
	//maybe check if av[1] is a .cub extension ?
	if (av[1])
		parse(av[1]);
	return (0);
}