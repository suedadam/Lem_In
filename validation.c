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

int		debug_print(t_input *input_d, char *line)
{
	(void)input_d;
	return (!ft_strcmp(line, "printall"));
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