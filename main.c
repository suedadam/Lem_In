/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 13:10:41 by asyed             #+#    #+#             */
/*   Updated: 2018/01/04 20:05:15 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdlib.h>
#include <stdio.h> //lol
#include <errno.h> //lol

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

int		print_all(t_input **input_d, char *line, int *op_i)
{
	t_rooms	*omg;

	printf("============\n");
	omg = (*input_d)->origin;
	while (omg)
	{
		printf("Room:\nName: %s\nX,Y: %d,%d\n\n", omg->name, omg->x, omg->y);
		omg = omg->next;
	}
	omg = (*input_d)->rooms;
	while (omg)
	{
		printf("Room:\nName: %s\nX,Y: %d,%d\n\n", omg->name, omg->x, omg->y);
		omg = omg->next;
	}
	omg = (*input_d)->dest;
	while (omg)
	{
		printf("Room:\nName: %s\nX,Y: %d,%d\n\n", omg->name, omg->x, omg->y);
		omg = omg->next;
	}
	printf("============\n");
	(void)line;
	(void)op_i;
	return (1);
}

int		debug_print(t_input *input_d, char *line)
{
	(void)input_d;
	return (!ft_strcmp(line, "printall"));
}

void	skip_char(char *str, int *i, char c)
{
	while (str[*i] == c)
		(*i)++;
}

int	word_c(char *str)
{
	int	i;

	i = 1;
	while (*str)
	{
		if (*str == ' ')
		{
			i++;
			while (*str && *str == ' ')
				str++;
		}
		else
			str++;
	}
	return (i);
}

int	valid_room(char *str, t_rooms *new)
{
	int	i;
	int tmp;

	if (word_c(str) != 3 || *str == 'L' || *str == '#')
		return (0);
	i = ft_strclen(str, ' ');
	str[i++] = '\0';
	new->name = ft_strdup(str);
	skip_char(str, &i, ' ');
	tmp = ft_atoi(&(str[i]));
	if (!tmp && str[i] != '0')
		return (0);
	new->x = tmp;
	i += ft_nbrlen(tmp);
	skip_char(str, &i, ' ');
	tmp = ft_atoi(&(str[i]));
	if (!tmp && str[i] != '0')
		return (0);
	new->y = tmp;
	return (1);
}

int	add_room(void **building, char *line)
{
	t_rooms	*new;

	new = ft_memalloc(sizeof(t_rooms));
	if (!new)
	{
		printf("Error in ft_memalloc(new)\n");
		return (0);
	}
	if (!valid_room(line, new))
	{
		free(new);
		return (0);
	}
	if (*building)
		new->next = *building;
	*building = new;
	return (1);
}

int	is_room(t_rooms *floor, char *room_name)
{
	while (floor)
	{
		if (!ft_strcmp(floor->name, room_name))
			return (1);
		floor = floor->next;
	}
	return (0);
}

int	p_command(t_input **input_d, char *line, int *op_i)
{
	if (!ft_strcmp(line, "##start"))
	{
		get_next_line(0, &line);
		if (!add_room((void **)&((*input_d)->origin), line))
			return (0);
	}
	else if (!ft_strcmp(line, "##end"))
	{
		get_next_line(0, &line);
		if (!add_room((void **)&((*input_d)->dest), line))
			return (0);
	}
	(void)op_i;
	return (1);
}

/*
** I don't really want to re-write another validation function lol
*/

int	is_valid_room(t_input *input_d, char *line)
{
	t_rooms	*new;

	new = ft_memalloc(sizeof(t_rooms));
	if (!new)
	{
		printf("Error in ft_memalloc(new)\n");
		return (0);
	}
	if (!valid_room(line, new))
	{
		free(new);
		return (0);
	}
	free(new);
	(void)input_d;
	return (1);
}

int	is_command(t_input *input_d, char *line)
{
	if (*line == '#' && line[1] == '#')
		return (1);
	(void)input_d;
	return (0);
}

int	is_link(t_input *input_d, char *line)
{
	char	*room;
	int		i;
	// t_rooms	*tmp;

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
	// i++;
	// printf("line[%d] = %c\n", i, line[i]);
	return (1);
}

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

int	new_room(t_input **input_d, char *line, int *op_i)
{
	get_next_line(0, &line);
	if (!add_room((void **)&((*input_d)->rooms), line))
		return (0);
	printf("=========\nRoom Created:\nName: \"%s\"\n", (*input_d)->origin->name);
	(void)op_i;
	return (1);
}

int	new_link(t_input **input_d, char *line, int *op_i)
{
	printf("Link lmao\n");
	(void)op_i;
	(void)input_d;
	(void)line;
	return (1);
}

int p_comment(t_input **input_d, char *line, int *op_i)
{
	printf("Comment = \"%s\"\n", line);
	(void)input_d;
	(void)op_i;
	return (1);
}

int	is_comment(t_input *input_d, char *line)
{
	if (*line == '#' && line[1] != '#')
		return (1);
	(void)input_d;
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