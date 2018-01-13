/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 20:05:49 by asyed             #+#    #+#             */
/*   Updated: 2018/01/04 20:06:42 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdlib.h>

int		debug_print(t_input *input_d, char *line)
{
	(void)input_d;
	if (!ft_strcmp(line, "printall"))
		return (1);
	return (0);
}

int		debug_print_links(t_input *input_d, char *line)
{
	(void)input_d;
	line = ft_strcdup(line, ' ');
	if (!ft_strcmp(line, "printlinks"))
		return (1);
	return (0);
}

int	is_link(t_input *input_d, char *line)
{
	char	*room;
	int		i;

	room = ft_strcdup(line, '-');
	if (!room || ft_strlen(room) == ft_strlen(line))
		return (0);
	if (!is_room(input_d->origin, room) && !is_room(input_d->rooms, room) && !is_room(input_d->dest, room))
	{
		printf("{SRC} Room name \"%s\" is not currently registered\n", room);
		free(room);
		return (-1);
	}
	i = ft_strclen(line, '-');
	if (line[i++] != '-')
	{
		printf("Error: line[%d] = %c instead of \'-\'\n", i - 1, line[i - 1]);
		free(room);
		return (-1);
	}
	if (!is_room(input_d->origin, &(line[i])) && !is_room(input_d->rooms, &(line[i])) && !is_room(input_d->dest, &(line[i])))
	{
		printf("{DEST} Room name \"%s\" is not currently registered\n", room);
		free(room);
		return (-1);
	}
	return (1);
}

int	find_not_num(const char *line, int length)
{
	int	i;

	i = 0;

	while (i < length)
	{
		if (!line[i] || line[i] < '0' || line[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	is_num(char *line)
{
	int	i;
	int	j;

	i = 0;
	j = ft_strclen(&(line[i]), ' ');
	if (find_not_num(&(line[i]), j))
		return (0);
	i = ++j;
	j = ft_strlen(&(line[i]));
	if (find_not_num(&(line[i]), --j))
		return (0);
	return (1);
}

int	is_valid_room(t_input *input_d, char *line)
{
	int	i;

	if (word_c(line) != 3 || *line == 'L' || *line == '#')
		return (0);
	i = ft_strclen(line, ' ');
	(void)input_d;
	return (is_num(&(line[++i])));
}

int	is_comment(t_input *input_d, char *line)
{
	if (*line == '#' && line[1] != '#')
		return (1);
	(void)input_d;
	return (0);
}

int	is_command(t_input *input_d, char *line)
{
	if (*line == '#' && line[1] == '#')
		return (1);
	(void)input_d;
	return (0);
}