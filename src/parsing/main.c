#include "cub3d.h"

void	print_map_tab(char **tab, t_vec2 size)
{
	int	i;

	i = 0;
	while (i < size.y)
	{
		printf("%s\n", tab[i]);
		i++;
	}
}

void	print_lst(t_lst *lst)
{
	t_lst	*tmp;

	tmp = lst;
	while (tmp)
	{
		printf("%s\n", tmp->tab);
		tmp = tmp->next;
	}
}

int	main(int ac, char **av, char **env)
{
	t_map	*map;

	if (!*env)
		return (printf("Error: env.\n"), EXIT_FAILURE);
	if (ac != 2)
		return (printf("Error: args number.\n"), EXIT_FAILURE);
	//maybe check if av[1] is a .cub extension ?
	map = parse(av[1]);
	if (!map)
		return (EXIT_FAILURE);
	//print_map_tab(map->map, map->map_size);
	// printf("no = %s \nso = %s \nwe = %s \nea = %s \n",
	// 	map->no, map->so, map->we, map->ea);
	// printf("f = %d, %d, %d\n", map->f.r, map->f.g, map->f.b);
	// printf("c = %d, %d, %d\n", map->c.r, map->c.g, map->c.b);
	// printf("player = %d, %d\n", map->player.x, map->player.y);
	free_map(map);
	return (0);
}
