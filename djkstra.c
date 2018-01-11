/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   djkstra.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 22:07:38 by asyed             #+#    #+#             */
/*   Updated: 2018/01/11 00:43:11 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	path_weight(t_rooms *src, t_rooms *dest)
{
	t_links	*tmp;

	tmp = src->to_link;
	while (tmp)
	{
		printf("%s->%s (dest = %s)\n", src->name,tmp->end->name, dest->name);
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
	int		res;

	node = (*input_d)->origin;
	neighbors = node->to_link;
	while (neighbors)
	{
		res = node_weight(neighbors->end);
		if (res > path_weight(node, neighbors->end))
		{
			neighbors->end->path = node;
			printf("Updated (%s's Prev = %s) new weight = %d!\n", neighbors->end->name, node->name, node_weight(neighbors->end));
		}
		else
		{
			printf("Failed? %d < %d\n", res, path_weight(node, neighbors->end));
		}
		neighbors = neighbors->next;
	}
	return (1);
}

int	dijkstra(t_input **input_d)
{
	t_rooms	*node;
	t_links	*neighbors;
	int		n_weight;

	node = (*input_d)->rooms;
	if (!dij_start(input_d))
	{
		printf("Failed to initialize neighbors from starting room.\n");
		return (0);
	}
	while (node)
	{
		n_weight = node_weight(node);
		neighbors = node->to_link;
		while (neighbors)
		{
			printf("{%s} neighbors: \"%s\" (%d)\n", node->name, neighbors->end->name, node_weight(neighbors->end));
			printf("path_weight = %d\n", path_weight(node, neighbors->end));
			if ((neighbors->end != (*input_d)->origin) && node_weight(neighbors->end) > n_weight + path_weight(node, neighbors->end))
			{
				neighbors->end->path = node;
				printf("Updated path = %s = %d\n", neighbors->end->name, node_weight(neighbors->end));
				// printf("Update: %s -> %s (neigh_weight = %d > %d + %d);New = %d\n", node->name, neighbors->end->name, node_weight(neighbors->end), n_weight, path_weight(node, neighbors->end), node_weight(neighbors->end));
			}
			else
			{
				printf("Already optimal path\n");
			}
			neighbors = neighbors->next;
		}
		printf("Node weight: %d\n", n_weight);
		node = node->next;
	}
	// Remove me.
	printf("\n===================\n");
	printf("Optimal path to |\"%s\"| (%d)\n", (*input_d)->dest->name, node_weight((*input_d)->dest));
	t_rooms	*optimal;

	optimal = (*input_d)->dest->path;
	while (optimal)
	{
		printf("%s\n", optimal->name);
		optimal = optimal->path;
	}
	//End remove me.
	return (1);
}