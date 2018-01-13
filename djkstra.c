/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   djkstra.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 22:07:38 by asyed             #+#    #+#             */
/*   Updated: 2018/01/12 16:03:23 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
		// printf("%s prev = %s\n", node->name, tmp->path->name);
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
			// neighbor_update(neighbors->end, input_d);
		}
		neighbors = neighbors->next;
	}
	return (1);
}

int	min_neighbor(t_rooms *node, t_input **input_d)
{
	// t_links	*min_neighbor;
	t_links	*neighbors;
	int		n_weight;
	int		ne_weight;
	int		p_weight;
	int		modified;

	printf("Stuck on node_weight()\n");
	n_weight = node_weight(node);
	printf("or am I?!\n");
	neighbors = node->to_link;
	modified = 0;
	while (neighbors)
	{
		printf("Fetching node_weight()\n");
		ne_weight = node_weight(neighbors->end);
		printf("Fetching path_weight()\n");
		p_weight = path_weight(node, neighbors->end);
		if (neighbors->end != (*input_d)->origin &&
			n_weight != INFINITY &&
			ne_weight > n_weight + p_weight)
		{
			printf("(M:%s N:%s) %d > %d + %d\n", node->name, neighbors->end->name, ne_weight, n_weight, p_weight);
			neighbors->end->path = node;
			modified++;
		}
		neighbors = neighbors->next;
	}
	return (modified);
}

int	list_update(t_rooms *node, t_input **input_d)
{
	int		res;
	t_rooms	*tmp;
	
	res = 1;
	while (node && res)
	{
		printf("==========Next itteration!!!!=======\n");
		res = 0;
		tmp = node;
		while (tmp)
		{
			printf("Next neighbor(%s)\n", tmp->name);
			res += min_neighbor(tmp, input_d);
			tmp = tmp->next;
		}
	}
	return (1);
}

int	dijkstra(t_input **input_d)
{
	t_rooms	*node;

	node = (*input_d)->rooms;
	if (!dij_start(input_d))
	{
		printf("Failed to initialize neighbors from starting room.\n");
		return (0);
	}
	list_update(node, input_d);
	printf("Done :)\n");
	printf("\n========== OP =========\n");
	printf("Optimal path to |\"%s\"|", (*input_d)->dest->name);
	printf(" (%d)\n", node_weight((*input_d)->dest));
	t_rooms	*optimal;

	optimal = (*input_d)->dest->path;
	while (optimal)
	{
		printf("%s\n", optimal->name);
		optimal = optimal->path;
	}
	return (1);
}