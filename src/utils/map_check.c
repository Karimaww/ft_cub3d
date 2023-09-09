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

int	check_colors(char **rgb, t_color *color)
{
	int	i;
	int	j;

	i = 0;
	while (rgb[i])
	{
		j = 0;
		while (rgb[i][j])
		{
			if (!ft_isdigit(rgb[i][j]))
				return (printf("Error: Bad colors.\n"), EXIT_FAILURE);
			j++;
		}
		i++;
	}
	if (i != 3)
		return (printf("Error: Bad colors.\n"), EXIT_FAILURE);
	color->r = ft_atoi(rgb[0]);
	color->g = ft_atoi(rgb[1]);
	color->b = ft_atoi(rgb[2]);
	if (color->r < 0 || color->r > 255 || color->g < 0 || color->g > 255
		|| color->b < 0 || color->b > 255)
		return (printf("Error: Bad colors.\n"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	check_player(t_map *map)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (i < map->map_size.y)
	{
		j = 0;
		while (map->map[i][j] && j < map->map_size.x)
		{
			if (map->map[i][j] == 'N' || map->map[i][j] == 'S'
				|| map->map[i][j] == 'E' || map->map[i][j] == 'W')
			{
				map->player.x = j;
				map->player.y = i;
				count++;
			}
			j++;
		}
		i++;
	}
	if (count != 1)
		return (printf("Error: Invalid number of players.\n"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	check_border(char **tab, int i, int j, int size)
{
	if (i == 0 || j == 0 || i == size - 1 || j == (int)ft_strlen(tab[i]) - 1)
		return (0);
	if (tab[i - 1][j] == ' ')
		return (0);
	if (tab[i + 1][j] == ' ')
		return (0);
	if (tab[i][j - 1] == ' ')
		return (0);
	if (tab[i][j + 1] == ' ')
		return (0);
	return (1);
}

int	check_wall(char **tab, int i, int j, int size)
{
	if (i == 0 || j == 0 || i == size - 1 || j == (int)ft_strlen(tab[i]) - 1)
		return (0);
	if (tab[i - 1][j] == '1' && tab[i + 1][j] == '1')
		return (1);
	if (tab[i][j - 1] == '1' && tab[i][j + 1] == '1')
		return (1);
	if (tab[i - 1][j] == '1' && tab[i + 1][j] != '1')
		return (0);
	if (tab[i][j - 1] == '1' && tab[i][j + 1] != '1')
		return (0);
	if (tab[i - 1][j] != '1' && tab[i + 1][j] == '1')
		return (0);
	if (tab[i][j - 1] != '1' && tab[i][j + 1] == '1')
		return (0);
	if (tab[i - 1][j] != '1' && tab[i + 1][j] != '1')
		return (0);
	if (tab[i][j - 1] != '1' && tab[i][j + 1] != '1')
		return (0);
	return (1);
}

int	check_isolation(char **tab, int size)
{
	int	j;
	int	i;

	i = 0;
	j = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			if (tab[i][j] == '0' && !check_border(tab, i, j, size))
				return (EXIT_FAILURE);
			if (tab[i][j] == '2' && (!check_wall(tab, i, j, size)
				|| !check_border(tab, i, j, size)))
				return (EXIT_FAILURE);
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
