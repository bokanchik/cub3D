/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandra <alexandra@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 13:01:31 by albokanc          #+#    #+#             */
/*   Updated: 2024/08/24 14:00:20 by alexandra        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../includes/cub3d.h"

int	check_first_last(char *line)
{
	int i;

	i = 0;
	while(line[i] && line[i] != '\n')
	{	
		if (line[i] != '1' && line[i] != ' ')
		{	
			//printf("at line  with index: %s\n%d\n", line, i);
			return (write(2, "Error. Map is not closed\n", 26), 0);
		}
		i++;
	}
	return (1);
}

int	check_borders(char *line)
{
	while (*line && ft_isspace(*line))
        line++;
	if (*line != '1' || line[ft_strlen(line) - 2] != '1')
	{
		//printf("at line : %s\n", line);
		return (write(2, "Error. Map is not closed\n", 26), 0);
	}
	return (1);
}

int	is_wall(char *line, int last, int i)
{
	if (i == 0 || i == last - 1)
	{
		if (!check_first_last(line))
			return (0);
	}
	else
	{
		if (!check_borders(line))
			return (0);
	}
	return (1);
}

int	is_closed(char **map, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		if (!is_wall(map[i], height, i))
			return (0);
		i++;
	}
	return (1);
}

int	check_char_in_line(char *line)
{
	int i;
	
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != 'N' \
			&& line[i] != 'S' && line[i] != 'W' && line[i] != 'E' && line[i] != ' ') 
			return (write(2, "Error. Values are not valid\n", 29), 0);
		i++;
	}
	return (1);
}

int is_valid_chars(char **map, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		if (!check_char_in_line(map[i]))
			return (0);
		i++;
	}
	return (1);
}
