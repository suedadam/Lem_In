/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 15:13:33 by asyed             #+#    #+#             */
/*   Updated: 2018/01/22 14:40:01 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdlib.h>

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
		*src_links = *new;
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
		exit(1);
	i = ft_strclen(line, '-');
	og_name = ft_strcdup(line, '-');
	dst_name = ft_strdup(&(line[++i]));
	new->end = find_room(input_d, dst_name);
	if (!(new->end))
		exit(1);
	src = find_room(input_d, og_name);
	if (!src)
		exit(1);
	if (!append_link(&(src->to_link), &new, 1))
		exit(1);
	storage = new->end;
	new = ft_memalloc(sizeof(t_links));
	if (!new)
		exit(1);
	new->end = src;
	if (!append_link(&(storage->to_link), &new, 1))
		exit(1);
	return (1);
}

int	new_room(t_input **input_d, char *line)
{
	if (!add_room((void **)&((*input_d)->rooms), line))
		return (0);
	return (1);
}

int p_comment(t_input **input_d, char *line)
{
	ft_putstr(line);
	(void)input_d;
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