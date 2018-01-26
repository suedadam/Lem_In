/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 15:13:33 by asyed             #+#    #+#             */
/*   Updated: 2018/01/26 15:26:17 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdlib.h>

int		append_link(t_links **src_links, t_links **new, int weight)
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

int		new_link(t_input **input_d, char *line)
{
	t_links	*new;
	char	*og_name;
	t_rooms	*storage;
	t_rooms	*src;
	int		i;

	if (!(new = ft_memalloc(sizeof(t_links))))
		return (0);
	i = ft_strclen(line, '-');
	og_name = ft_strcdup(line, '-');
	new->end = find_room(input_d, ft_strdup(&(line[++i])));
	if (!(new->end))
		return (0);
	if (!(src = find_room(input_d, og_name)))
		return (0);
	if (!append_link(&(src->to_link), &new, 1))
		return (0);
	storage = new->end;
	if (!(new = ft_memalloc(sizeof(t_links))))
		return (0);
	new->end = src;
	if (!append_link(&(storage->to_link), &new, 1))
		return (0);
	return (1);
}

int		new_room(t_input **input_d, char *line)
{
	if (!add_room((void **)&((*input_d)->rooms), line))
		return (0);
	return (1);
}

int		p_comment(t_input **input_d, char *line)
{
	ft_putstr(line);
	(void)input_d;
	return (1);
}

int		p_command(t_input **input_d, char *line)
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
