/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksadykov <ksadykov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 21:16:33 by ksadykov          #+#    #+#             */
/*   Updated: 2023/09/23 15:11:11 by ksadykov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*repeat_char(char c, int n)
{
	char	*str;

	str = (char *)malloc(n + 1);
	if (!str)
		return (NULL);
	memset(str, c, n);
	str[n] = '\0';
	return (str);
}

int	space_extension(char **map, int x)
{
	int		i;
	char	*tmp;
	char	*spaces;

	i = 0;
	tmp = NULL;
	while (map[i])
	{
		if ((int)ft_strlen(map[i]) < x)
		{
			tmp = map[i];
			spaces = repeat_char(' ', x - ft_strlen(map[i]));
			if (!spaces)
				return (0);
			map[i] = ft_strjoin(map[i], spaces);
			if (!map[i])
				return (0);
			free(tmp);
			free(spaces);
		}
		i++;
	}
	return (1);
}

int	put_dir(char **dir, char *line)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	if (*dir)
		return (printf("Error\nDouble declaration of map parameter.\n"),
			EXIT_FAILURE);
	while (line[i] == ' ')
		i++;
	while (line[i + len] && line[i + len] != ' ' && line[i + len] != '\n')
		len++;
	if (len == 0)
		return (printf("Error\nNo file to use.\n"), EXIT_FAILURE);
	*dir = ft_substr(line, i, len);
	if (!*dir)
		return (printf("Error\nNo directory: malloc error.\n"), EXIT_FAILURE);
	if (access(*dir, F_OK) == -1)
		return (printf("Error\nFile does not exist.\n"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	put_color(t_color *color, char *line)
{
	int		i;
	int		len;
	char	**rgb;
	char	*subline;

	i = 0;
	len = 0;
	if (color->r != -1 || color->g != -1 || color->b != -1)
		return (printf("Error\nDouble declaration of map parameter.\n"),
			EXIT_FAILURE);
	while (line[i] == ' ')
		i++;
	while (line[i + len] && line[i + len] != ' ' && line[i + len] != '\n')
		len++;
	if (len == 0)
		return (printf("Error\nNo color is given.\n"), EXIT_FAILURE);
	subline = ft_substr(line, i, len);
	if (!subline)
		return (EXIT_FAILURE);
	rgb = ft_split(subline, ',');
	if (!rgb)
		return (free(subline), EXIT_FAILURE);
	if (check_colors(rgb, color) == EXIT_FAILURE)
		return (free(subline), free_tab(rgb), EXIT_FAILURE);
	return (free(subline), free_tab(rgb), EXIT_SUCCESS);
}

int	get_param(t_map **map, char *line)
{
	int		i;
	int		res;

	i = 0;
	res = -1;
	while (line[i] && line[i] != '\n')
	{
		res = -1;
		find_dir(map, line, &res, i);
		if (res == EXIT_SUCCESS || res == EXIT_FAILURE)
			return (res);
		if (line[i] != ' ')
			return (printf("Error\nInvalid map parameter.\n"),
				EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
