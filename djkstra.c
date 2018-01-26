/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   djkstra.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 22:07:38 by asyed             #+#    #+#             */
/*   Updated: 2018/01/26 15:34:31 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdlib.h>

int		dij_start(t_input **input_d)
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

int		neighbor_update(t_rooms *node, t_input **input_d)
{
	int		n_weight;
	t_links	*neighbors;

	n_weight = node_weight(node);
	neighbors = node->to_link;
	while (neighbors)
	{
		if (neighbors->end != (*input_d)->origin &&
			(n_weight == INFINITY ||
				node_weight(neighbors->end) > n_weight +
				path_weight(node, neighbors->end)))
		{
			neighbors->end->path = node;
		}
		neighbors = neighbors->next;
	}
	return (1);
}

int		min_neighbor(t_rooms *node, t_input **input_d)
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

char	*push_all(t_input **input_d)
{
	static int	i = 0;
	t_rooms		*rooms;
	char		*str;

	str = NULL;
	rooms = (*input_d)->dest;
	while (rooms && rooms->path)
	{
		if (rooms->path->ants && !push_ant(&str, rooms, input_d))
			exit(1);
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
		if (!move_join(&str, rooms))
			exit(1);
	}
	return (str);
}

int		dijkstra(t_input **input_d)
{
	t_rooms	*node;

	if (!(node = (*input_d)->rooms))
	{
		ft_putstr("Error\n");
		exit(1);
	}
	if (!dij_start(input_d))
		exit(1);
	list_update(input_d);
	push_ants(input_d);
	return (1);
}
