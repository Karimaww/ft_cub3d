/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksadykov <ksadykov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 21:17:39 by ksadykov          #+#    #+#             */
/*   Updated: 2023/09/15 21:17:39 by ksadykov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	lst_add_back(t_lst **lst, char *tab)
{
	t_lst	*new;
	t_lst	*tmp;
	int		len;

	new = malloc(sizeof(t_lst));
	len = ft_strlen(tab);
	if (!new)
		return (printf("Error: Malloc error\n"), EXIT_FAILURE);
	if (tab[ft_strlen(tab) - 1] == '\n')
		len = ft_strlen(tab) - 1;
	new->tab = ft_substr(tab, 0, len);
	new->size = len;
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

int	free_lst(t_lst **lst)
{
	t_lst	*tmp;

	if (!*lst)
		return (EXIT_SUCCESS);
	while (*lst)
	{
		tmp = (*lst)->next;
		if ((*lst)->tab)
			free((*lst)->tab);
		free(*lst);
		*lst = tmp;
	}
	lst = NULL;
	return (EXIT_SUCCESS);
}

int	lst_size(t_lst *lst)
{
	int		i;
	t_lst	*tmp;

	i = 0;
	tmp = lst;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}
