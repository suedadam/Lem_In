/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 14:46:29 by asyed             #+#    #+#             */
/*   Updated: 2018/01/26 14:55:23 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_links	*find_link(t_rooms *src, t_rooms *node)
{
	t_links	*itt;

	itt = src->to_link;
	while (itt)
	{
		if (itt->end == node)
			return (itt);
		itt = itt->next;
	}
	return (NULL);
}

int		del_lastl(t_rooms **node, t_links *link)
{
	t_links	*start;

	start = (*node)->to_link;
	if (start->prev->next)
		exit(1);
	start->prev = link->prev;
	return (1);
}

int		reposition_link(t_links *link, t_rooms **node)
{
	t_links	*save;

	if (link->prev == link)
	{
		free((*node)->to_link);
		(*node)->to_link = NULL;
		return (1);
	}
	if (link->prev->next)
		link->prev->next = link->next;
	if (link->next)
		link->next->prev = link->prev;
	save = link;
	link = link->prev;
	while (link->prev->next)
		link = link->prev;
	(*node)->to_link = link;
	free(save);
	return (1);
}

int		delete_link(t_rooms **node, t_rooms **findme)
{
	t_links	*link;

	link = (*node)->to_link;
	while (link)
		if (link->end == *findme)
		{
			if (link == (*node)->to_link)
				reposition_link(link, node);
			else
			{
				if (link->prev->next)
					link->prev->next = link->next;
				if (link->next)
					link->next->prev = link->prev;
				else if (!del_lastl(node, link))
					exit(1);
				free(link);
			}
			return (1);
		}
		else
			link = link->next;
	return (0);
}

int		is_num(char *line)
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
