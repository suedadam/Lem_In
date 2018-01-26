/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   djkstra.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suedadam <suedadam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 22:07:38 by asyed             #+#    #+#             */
/*   Updated: 2018/01/25 03:07:26 by suedadam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdlib.h>

int	path_weight(t_rooms *src, t_rooms *dest)
{
	t_links	*tmp;

	tmp = src->to_link;
	while (tmp)
	{
		if (tmp->end == dest)
			return (tmp->weight);
		tmp = tmp->next;
	}
	return (0);
}

int	node_weight(t_rooms *node)
{
	int		weight;
	t_rooms	*tmp;

	weight = 0;
	tmp = node;
	while (tmp->path)
	{
		weight += path_weight(tmp->path, tmp);
		tmp = tmp->path;
	}
	return (weight ? weight : INFINITY);
}

int	dij_start(t_input **input_d)
{
	t_rooms	*node;
	t_links	*neighbors;

	node = (*input_d)->origin;
	neighbors = node->to_link;
	while (neighbors)
	{
		if (find_link(node, neighbors->end))
			neighbors->end->path = node;
		neighbors = neighbors->next;
	}
	neighbors = node->to_link;
	while (neighbors)
	{
		neighbor_update(neighbors->end, input_d);
		neighbors = neighbors->next;
	}
	return (1);
}

int	neighbor_update(t_rooms *node, t_input **input_d)
{
	int		n_weight;
	t_links	*neighbors;

	n_weight = node_weight(node);
	neighbors = node->to_link;
	while (neighbors)
	{
		if (neighbors->end != (*input_d)->origin &&
			(n_weight == INFINITY ||
				node_weight(neighbors->end) > n_weight + path_weight(node, neighbors->end)))
		{
			neighbors->end->path = node;
		}
		neighbors = neighbors->next;
	}
	return (1);
}

int	min_neighbor(t_rooms *node, t_input **input_d)
{
	t_links	*neighbors;
	int		n_weight;
	int		ne_weight;
	int		p_weight;
	int		modified;

	n_weight = node_weight(node);
	neighbors = node->to_link;
	modified = 0;
	while (neighbors)
	{
		ne_weight = node_weight(neighbors->end);
		p_weight = path_weight(node, neighbors->end);
		if (neighbors->end != (*input_d)->origin &&
			n_weight != INFINITY &&
			ne_weight > n_weight + p_weight)
		{
			neighbors->end->path = node;
			modified++;
		}
		neighbors = neighbors->next;
	}
	return (modified);
}

int	list_update(t_input **input_d)
{
	int		res;
	t_rooms	*tmp;
	
	res = 1;
	while (res)
	{
		res = 0;
		tmp = (*input_d)->rooms;
		while (tmp)
		{
			res += min_neighbor(tmp, input_d);
			tmp = tmp->next;
		}
	}
	return (1);
}

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

int	del_lastl(t_rooms **node, t_links *link)
{
	t_links	*start;

	start = (*node)->to_link;
	if (start->prev->next)
		exit(1);
	start->prev = link->prev;
	return (1);
}

int	reposition_link(t_links *link, t_rooms **node)
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

int	delete_link(t_rooms **node, t_rooms **findme)
{
	t_links	*link;
	t_links	*save;

	link = (*node)->to_link;
	while (link)
	{
		if (link->end == *findme)
		{
			if (link == (*node)->to_link)
			{
				reposition_link(link, node);
				link = (*node)->to_link;
			}
			else
			{
				if (link->prev->next)
					link->prev->next = link->next;
				if (link->next)
					link->next->prev = link->prev;
				else if (!del_lastl(node, link))
						exit(1);
				save = link;
				link = link->prev;
				free(save);
			}
			return (1);
		}
		link = link->next;
	}
	return (0);
}

char	*room_move(char *src, char *dst)
{
	char	*str;

	if (!(str = ft_memalloc(ft_strlen(src) + ft_strlen(dst) + 2)))
		exit(1);
	str[0] = 'L';
	if (!(ft_strcat(str, src)))
		exit(1);
	str[ft_strlen(str)] = '-';
	if (!(ft_strcat(str, dst)))
		exit(1);
	return (str);
}

int		size_gen(t_input **input_d)
{
	int		i;
	t_rooms	*node;

	i = 0;
	node = (*input_d)->dest;
	while (node)
	{
		i += ft_strlen(node->name) + 24;
		node = node->path;
	}
	return (i);
}

char	*push_all(t_input **input_d)
{
	static	int i = 0;
	t_rooms	*rooms;
	char	*str;
	char	*tmp;

	str = NULL;
	tmp = NULL;
	rooms = (*input_d)->dest;
	while (rooms && rooms->path)
	{
		if (rooms->path->ants)
		{
			if (!str && !(str = ft_memalloc(size_gen(input_d))))
				exit(1);
			rooms->ants = rooms->path->ants;
			rooms->path->ants = 0;
			if (!(tmp = room_move(ft_itoa(rooms->ants), rooms->name)))
				exit(1);
			if (!ft_strcat(str, tmp))
				exit(1);
			ft_strcat(str, " ");
		}
		rooms = rooms->path;
	}
	if (i < (*input_d)->ants)
	{
		if (!str && !(str = ft_memalloc(size_gen(input_d))))
			exit(1);
		rooms = (*input_d)->dest;
		while (rooms && rooms->path->next)
			rooms = rooms->path;
		rooms->ants = ++i;
		if (!(tmp = room_move(ft_itoa(rooms->ants), rooms->name)))
			exit(1);
		ft_strcat(str, tmp);
	}
	return (str);
}

int	lost_ants(t_input **input_d)
{
	t_rooms	*node;

	node = (*input_d)->dest;
	while (node)
	{
		if (node->ants)
			return (1);
		node = node->path;
	}
	return (0);
}

int	push_ants(t_input **input_d)
{
	int		i;
	t_rooms	*first;
	char	 *tmp;

	i = 1;
	first = (*input_d)->dest;
	while (first && first->path->next)
		first = first->path;
	while (i <= (*input_d)->ants || lost_ants(input_d))
	{
		if (!(tmp = push_all(input_d)))
			exit(0);
		ft_putstr(tmp);
		ft_putchar('\n');
		free(tmp);
		i++;
	}
	return (1);
}

int	dijkstra(t_input **input_d)
{
	t_rooms	*node;

	node = (*input_d)->rooms;
	if (!dij_start(input_d))
		exit(1);
	list_update(input_d);
	push_ants(input_d);
	return (1);
}