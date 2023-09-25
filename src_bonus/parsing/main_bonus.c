/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksadykov <ksadykov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 21:17:32 by ksadykov          #+#    #+#             */
/*   Updated: 2023/09/15 21:17:32 by ksadykov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	main(int ac, char **av, char **env)
{
	t_map	*map;
	t_cub	*cub;

	if (!*env)
		return (printf("Error\nEnvironment is not set.\n"), EXIT_FAILURE);
	if (ac != 2)
		return (printf("Error\nInvalid number of arguments.\n"), EXIT_FAILURE);
	srand(time(NULL));
	if (ft_strlen(av[1]) < 4
		|| strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4))
		return (printf("Error\nPUT .cub :)\n"), EXIT_FAILURE);
	map = parse(av[1]);
	if (!map)
		return (get_next_line(-42), EXIT_FAILURE);
	cub = init_cub(map);
	if (!cub)
		return (printf("Error\nInit cub\n"), free_map(map), EXIT_FAILURE);
	mlx_loop(cub->mlx.mlx);
	return (0);
}
