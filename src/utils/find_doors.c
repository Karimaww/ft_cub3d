#include "cub3d.h"

int	door_add_back(t_door **lst, t_vec2 pos)
{
	t_door	*new;
	t_door	*tmp;

	new = malloc(sizeof(t_door));
	if (!new)
		return (printf("Error: Malloc error\n"), EXIT_FAILURE);
	new->pos = pos;
	new->open = 0;
	new->next = NULL;
	if (!*lst)
	{
		*lst = new;
		return (EXIT_SUCCESS);
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (EXIT_SUCCESS);
}

int	free_door(t_door **lst)
{
	t_door	*tmp;

	if (!*lst)
		return (EXIT_SUCCESS);
	while (*lst)
	{
		tmp = (*lst)->next;
		free(*lst);
		*lst = tmp;
	}
	lst = NULL;
	return (EXIT_SUCCESS);
}

int	find_doors(t_map **map)
{
	int	j;
	int	i;

	i = 0;
	j = 0;
	while ((*map)->map[i])
	{
		j = 0;
		while ((*map)->map[i][j])
		{
			if ((*map)->map[i][j] == '2'
				&& door_add_back(&((*map)->lst_doors), (t_vec2){i, j, 0})
					== EXIT_FAILURE)
				return (EXIT_FAILURE);
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
