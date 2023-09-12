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

int	main(int ac, char **av, char **env)
{
	t_map	*map;
	t_cub	*cub;

	if (!*env)
		return (printf("Error: env.\n"), EXIT_FAILURE);
	if (ac != 2)
		return (printf("Error: args number.\n"), EXIT_FAILURE);
	srand(time(NULL));
	//maybe check if av[1] is a .cub extension ?
	map = parse(av[1]);
	if (!map)
		return (get_next_line(-42), EXIT_FAILURE);
	print_map_tab(map->map, map->map_size);
	printf("no = %s \nso = %s \nwe = %s \nea = %s \n",
		map->no, map->so, map->we, map->ea);
	printf("f = %d, %d, %d\n", map->f.r, map->f.g, map->f.b);
	printf("c = %d, %d, %d\n", map->c.r, map->c.g, map->c.b);
	printf("player = %d, %d\n", map->player.x, map->player.y);
	cub = init_cub(map);
	if (!cub)
		return (printf("Error: init cub.\n"), free_map(map), EXIT_FAILURE);
	mlx_loop(cub->mlx.mlx);
	//free_map(map);
	return (0);
}
