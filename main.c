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

struct s_operations ops[] = {
	{"total ants", &total_ants},
	{"function chooser", &choose_func}
};

struct s_syntax validator[] = {
	{"link", &is_link, &new_link},
	{"comments", &is_comment, &p_comment},
	{"command", &is_command, &p_command},
	// {"Normal room add", &is_valid_room, &new_room},
	{"debugger print all", &debug_print, &print_all},
	{NULL, NULL, NULL}
};

int	choose_func(t_input **input_d, char *line, int *op_i)
{
	int		i;
	int		res;

	i = 0;
	while (validator[i].match)
	{
		if ((res = validator[i].match(*input_d, line)) == 1)
			return (validator[i].exec(input_d, line, op_i));
		if (res == -1)
			return (0);
		i++;
	}
	(void)op_i;
	return (0);
}

int	comment_parse(char *line)
{
	printf("Comment = \"%s\"\n", line);
	return (1);
}

int	total_ants(t_input **input_d, char *line, int *op_i)
{
	if (*line == '#')
	{
		if (line[1] && line[1] == '#')
			return (0);
		else if (comment_parse(line))
			return (1);
		else
			return (0);
	}
	if ((*input_d)->ants)
		return (0);
	(*input_d)->ants = ft_atoi(line);
	if (!(*input_d)->ants)
		return (0);
	*op_i = 1;
	return (1);
}

int	parse_input(t_input **input_d)
{
	char	*line;
	int		i;

	line = NULL;
	i = 0;
	while (get_next_line(0, &line))
	{
		printf("B: i = %d\n", i);
		if (!ops[i].func(input_d, line, &i))
		{
			printf("Error: Failed to execute \"%s\" func\n", ops[i].op_name);
			free(line);
			line = NULL;
			return (0);
		}
		printf("A: i = %d\n", i);
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