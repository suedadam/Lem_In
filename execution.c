/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 20:07:13 by asyed             #+#    #+#             */
/*   Updated: 2018/01/04 20:09:36 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	new_link(t_input **input_d, char *line, int *op_i)
{
	printf("Link lmao\n");
	(void)op_i;
	(void)input_d;
	(void)line;
	return (1);
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

int p_comment(t_input **input_d, char *line, int *op_i)
{
	printf("Comment = \"%s\"\n", line);
	(void)input_d;
	(void)op_i;
	return (1);
}

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