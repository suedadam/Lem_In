/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 15:13:33 by asyed             #+#    #+#             */
/*   Updated: 2018/01/09 22:38:45 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_rooms	*find_room(t_input **input_d, char *room_name)
{
	t_rooms	*ret;

	ret = NULL;
	if (!ret)
		ret = is_room((*input_d)->origin, room_name);
	if (!ret)
		ret = is_room((*input_d)->rooms, room_name);
	if (!ret)
		ret = is_room((*input_d)->dest, room_name);
	return (ret);
}

int append_link(t_links **src_links, t_links **new, int weight)
{
	t_links	*tmp;

	if (!*src_links)
	{
		*src_links = *new;
		tmp = (*src_links);
	}
	else
	{
		tmp = (*src_links);
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = (*new);
		(*new)->prev = tmp;
	}
	(*src_links)->prev = (*new);
	(*new)->weight = weight;
	return (1);
}

int	new_link(t_input **input_d, char *line)
{
	t_links	*new;
	char	*og_name;
	char	*dst_name;
	t_rooms	*storage;
	t_rooms	*src;
	int		i;

	new = ft_memalloc(sizeof(t_links));
	if (!new)
	{
		printf("Failed to malloc()\n");
		return (0);
	}
	i = ft_strclen(line, '-');
	og_name = ft_strcdup(line, '-');
	dst_name = ft_strdup(&(line[++i]));
	new->end = find_room(input_d, dst_name);
	if (!(new->end))
	{
		printf("End room \"%s\" not found\n", dst_name);
		return (0);
	}
	src = find_room(input_d, og_name);
	if (!src)
	{
		printf("SRC room \"%s\" not found\n", og_name);
		return (0);
	}
	if (!append_link(&(src->to_link), &new, 1))
	{
		printf("Failed to append\n");
		return (0);
	}
	storage = new->end;
	new = ft_memalloc(sizeof(t_links));
	if (!new)
	{
		printf("Failed to malloc()\n");
		return (0);
	}
	new->end = src;
	if (!append_link(&(storage->to_link), &new, 1))
	{
		printf("Failed to append\n");
		return (0);
	}
	return (1);
}

int	new_room(t_input **input_d, char *line)
{
	if (!add_room((void **)&((*input_d)->rooms), line))
		return (0);
	printf("=========\nRoom Created:\nName: \"%s\"\n", (*input_d)->rooms->name);
	return (1);
}

int p_comment(t_input **input_d, char *line)
{
	printf("Comment = \"%s\"\n", line);
	(void)input_d;
	return (1);
}

int	print_links(t_input **input_d, char *line)
{
	int 	i;
	t_rooms *room;
	
	i = ft_strclen(line, ' ');
	room = find_room(input_d, &(line[++i]));
	printf("=======\n");
	while (room->to_link)
	{
		printf("Room link is to room \"%s\"\n", room->to_link->end->name);
		room->to_link = room->to_link->next;
	}
	return (1);
}

int		print_all(t_input **input_d, char *line)
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
	return (1);
}

int	p_command(t_input **input_d, char *line)
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
	return (1);
}