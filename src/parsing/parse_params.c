#include "cub3d.h"

int	put_dir(char **dir, char *line)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	if (*dir)
		return (printf("Error: Double declaration.\n"), EXIT_FAILURE);
	while (line[i] == ' ')
		i++;
	while (line[i + len] && line[i + len] != ' ' && line[i + len] != '\n')
		len++;
	if (len == 0)
		return (printf("Error: No file to use.\n"), EXIT_FAILURE);
	*dir = ft_substr(line, i, len);
	if (access(*dir, F_OK) == -1)
		return (printf("Error: File does not exist.\n"), EXIT_FAILURE);
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
		return (printf("Error: Double declaration.\n"), EXIT_FAILURE);
	while (line[i] == ' ')
		i++;
	while (line[i + len] && line[i + len] != ' ' && line[i + len] != '\n')
		len++;
	if (len == 0)
		return (printf("Error: No color is given.\n"), EXIT_FAILURE);
	subline = ft_substr(line, i, len);
	rgb = ft_split(subline, ',');
	if (!rgb || check_colors(rgb, color) == EXIT_FAILURE)
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
		if (!ft_strncmp(line + i, "NO", 2) && line[i + 2] == ' ')
			res = put_dir(&((*map)->no), line + i + 2);
		else if (!ft_strncmp(line + i, "SO", 2) && line[i + 2] == ' ')
			res = put_dir(&((*map)->so), line + i + 2);
		else if (!ft_strncmp(line + i, "WE", 2) && line[i + 2] == ' ')
			res = put_dir(&((*map)->we), line + i + 2);
		else if (!ft_strncmp(line + i, "EA", 2) && line[i + 2] == ' ')
			res = put_dir(&((*map)->ea), line + i + 2);
		else if (!ft_strncmp(line + i, "F", 1) && line[i + 1] == ' ')
			res = put_color(&((*map)->f), line + i + 1);
		else if (!ft_strncmp(line + i, "C", 1) && line[i + 1] == ' ')
			res = put_color(&((*map)->c), line + i + 1);
		if (res == EXIT_SUCCESS)
			return (EXIT_SUCCESS);
		if (line[i] != ' ' || res == EXIT_FAILURE)
			return (printf("Error: Bad params.\n"), EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
