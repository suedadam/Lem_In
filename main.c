/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 13:10:41 by asyed             #+#    #+#             */
/*   Updated: 2018/01/15 15:34:34 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdlib.h>
#include <stdio.h> //lol
#include <errno.h> //lol
//*Deete me
#include <sys/stat.h> 
#include <fcntl.h>
//End delete me

// http://macfreek.nl/memory/Disjoint_Path_Finding

struct s_syntax validator[] = {
	{"link", &is_link, &new_link},
	{"comments", &is_comment, &p_comment},
	{"command", &is_command, &p_command},
	{"Normal room add", &is_valid_room, &new_room},
	{NULL, NULL, NULL}
};


int	print_weight(t_input **input_d, char *line)
{
	t_rooms	*room;
	int		weight;
	char	*room_name;
	int		i;

	i = ft_strclen(line, ' ');
	room_name = ft_strdup(&(line[++i]));
	room = find_room(input_d, room_name);
	(void)weight;
	return (1);
}

int	debug_weight(t_input *input_d, char *line)
{
	(void)input_d;
	line = ft_strcdup(line, ' ');
	if (!ft_strcmp(line, "weightprint"))
		return (1);
	return (0);
}

int	comment_parse(char *line)
{
	ft_putstr(line);
	return (1);
}

int	total_ants(t_input **input_d)
{
	char	*line;

	line = NULL;
	while (get_next_line(0, &line))
	{
		if (*line == '#')
		{
			if (line[1] && line[1] == '#')
				return (0);
			else if (comment_parse(line))
				continue ;
			else
				return (0);
		}
		if ((*input_d)->ants)
			return (0);
		(*input_d)->ants = ft_atoi(line);
		if (!(*input_d)->ants)
			return (0);
		return (1);
	}
	return (0);
}

int	parse_input(t_input **input_d)
{
	char	*line;
	int		i;
	int		res;

	line = NULL;
	if (!total_ants(input_d))
		return (0);
	while (get_next_line(0, &line))
	{
		i = 0;
		while (validator[i].match)
		{
			if ((res = validator[i].match(*input_d, line)) == 1)
			{
				if (validator[i].exec(input_d, line))
					break ;
				else
					return (0);
			}
			if (res == -1)
				return (0);
			i++;
		}
		if (!validator[i].match)
			return (0);
		free(line);
		line = NULL;
	}
	return (1);
}

int	main(void)
{
	t_input	*input_d;

	input_d = ft_memalloc(sizeof(t_input));
	if (!input_d)
		exit(1);
	if (parse_input(&input_d))
		dijkstra(&input_d);
	else
		ft_putstr("Error\n");
	return (0);
}