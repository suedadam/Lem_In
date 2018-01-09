/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 13:10:41 by asyed             #+#    #+#             */
/*   Updated: 2018/01/04 21:01:31 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdlib.h>
#include <stdio.h> //lol
#include <errno.h> //lol

// http://macfreek.nl/memory/Disjoint_Path_Finding

struct s_syntax validator[] = {
	{"link", &is_link, &new_link},
	{"comments", &is_comment, &p_comment},
	{"command", &is_command, &p_command},
	{"Normal room add", &is_valid_room, &new_room},
	{"debugger print all", &debug_print, &print_all},
	{NULL, NULL, NULL}
};

int	comment_parse(char *line)
{
	printf("Comment = \"%s\"\n", line);
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
				printf("Passed match(\"%s\")\n", validator[i].op_name);
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
	{
		printf("Error: %s\n", strerror(errno));
		return (-1);
	}
	if (parse_input(&input_d))
	{
		// ..
	}
	else
		printf("Error\n"); //Change to ft_printf
	return (0);
}