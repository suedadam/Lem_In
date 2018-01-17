/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   djkstra.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 22:07:38 by asyed             #+#    #+#             */
/*   Updated: 2018/01/17 15:26:09 by asyed            ###   ########.fr       */
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
		// printf("%s == %s\n", tmp->end->name, dest->name);
		if (tmp->end == dest)
		{
			// printf("Returned weight\n");
			return (tmp->weight);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	backwards_node_weight(t_rooms *node)
{
	int		weight;
	t_rooms	*tmp;

	weight = 0;
	tmp = node;
	while (tmp->path)
	{
		printf("(%s)%d += (%s)%d\n", tmp->name, weight, tmp->path->name, path_weight(tmp, tmp->path));
		weight += path_weight(tmp, tmp->path);
		tmp = tmp->path;
	}
	return (weight ? weight : INFINITY);
}

int	node_weight(t_rooms *node)
{
	int		weight;
	t_rooms	*tmp;

	weight = 0;
	tmp = node;
	while (tmp->path)
	{
		printf("(%s)%d += (%s)%d\n", tmp->path->name, weight, tmp->name, path_weight(tmp->path, tmp));
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

int	in_path(t_rooms *path, t_rooms *subpath)
{
	while (path)
	{
		if (path == subpath)
			return (1);
		path = path->path;
	}
	return (0);
}

int	del_lastl(t_links *links)
{
	t_links	*tmp;

	tmp = links;
	while (tmp && tmp->prev->next)
		tmp = tmp->prev;
	printf("First = \"%s\"\n", tmp->end->name);
	if (!tmp)
	{
		printf("Failed del_lastl()\n");
		return (0);
	}
	tmp->prev = tmp->prev->prev;
	return (1);
}

int	print_linkstest(t_rooms *src, t_rooms **dest)
{
	t_links	*link;

	link = src->to_link;
	while (link)
	{
		printf("{TEST} %s -> %s\n", src->name, link->end->name);
		link = link->next;
	}
	return (1);
	(void)dest;
}

int	delete_link(t_rooms *src, t_rooms **dest)
{
	t_links	*link;

	link = find_link(src, *dest);
	if (!link)
	{
		printf("Not found.\n");
		return (0);
	}
	link->prev->next = link->next;
	if (link->next)
		link->next->prev = link->prev;
	else
	{
		printf("Last link (%s->%s)\n", src->name, link->end->name);
		if (!del_lastl(link))
			return (0);
	}
	free(link);
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

int	inverse_weight(t_links *link)
{
	if (link && link->weight > 0)
	{
		link->weight = -link->weight;
		return (1);
	}
	return (0);
}

int	reverse_direction(t_rooms *dest)
{
	t_rooms	*optimal;

	optimal = dest;
	while (optimal && optimal->path)
	{
		delete_link(optimal->path, &optimal);
		if (!inverse_weight(find_link(optimal, optimal->path)))
		{
			printf("Failed to inverse weight\n");
			return (0);
		}
		optimal = optimal->path;
	}
	return (1);
}

int	forward_direction(t_rooms *dest)
{
	t_rooms	*optimal;

	optimal = dest;
	while (optimal && optimal->path)
	{
		// printf("Deleting link from %s -> %s\n", optimal->name, optimal->path->name);
		if (!delete_link(optimal, &(optimal->path)))
			return (0);
		// printf("Deleted.\n");
		optimal = optimal->path;
	}
	return (1);
}

int	inverse_optimal(t_rooms **node, t_input **input_d)
{
	t_rooms *i_node;

	reverse_direction((*input_d)->dest);
	i_node = *node;
	while (i_node)
	{
		printf("Room: \"%s\" is *NOT* present\n", i_node->name);
		i_node->path = NULL;
		i_node = i_node->next;
	}
	(*input_d)->dest->path = NULL;
	return (1);
}

// int	sum_paths(t_rooms *node, t_input **input_d, uint8_t directional)
// {
// 	t_rooms	*i_node;

// 	i_node = *node;
// 	while (i_node)
// 	{
// 		//...
// 		i_node = i_node->next;
// 	}
// }

int	dijkstra(t_input **input_d)
{
	t_rooms	*node;

	node = (*input_d)->rooms;
	if (!dij_start(input_d))
	{
		printf("Failed to initialize neighbors from starting room.\n");
		return (0);
	}
	printf("Dest: %s->%s\n", (*input_d)->dest->name, ((*input_d)->dest->next) ? (*input_d)->dest->next->name : "NULL");
	list_update(node, input_d);
	// //debug
	// while (node)
	// {
	// 	if (!ft_strcmp(node->name, "337"))
	// 	{
	// 		printf("Found it.\n");
	// 		t_links *lol;
	// 		lol = node->to_link;
	// 		while (lol)
	// 		{
	// 			printf("lol = %s <- (%s;%s) -> %s\n", lol->prev->end->name, node->name, lol->end->name, (lol->next) ? lol->next->end->name : "NULL");
	// 			lol = lol->next;
	// 		}
	// 		delete_link(node, &((*input_d)->dest));
	// 		lol = node->to_link;
	// 		while (lol)
	// 		{
	// 			printf("lol = %s <-", lol->prev->end->name);
	// 			printf(" %s ->", node->name);
	// 			printf(" %s\n", lol->end->name);
	// 			// printf("lol = %s <- %s -> %s\n", lol->prev->end->name, node->name, lol->end->name);
	// 			lol = lol->next;
	// 		}
	// 	}
	// 	node = node->next;
	// }
	inverse_optimal(&node, input_d);
	printf("Done :)\n");
	printf("\n========== OP =========\n");
	printf("Optimal path to |\"%s\"|", (*input_d)->dest->name);
	printf(" (%d)\n", backwards_node_weight((*input_d)->dest));
	t_rooms	*optimal;

	optimal = (*input_d)->dest->path;
	while (optimal)
	{
		printf("%s\n", optimal->name);
		optimal = optimal->path;
	}
	printf("\n========= E-OP ========\n");
	if (!dij_start(input_d))
	{
		printf("BITCH WHY YOU FAILING THE 2ND TIME AROUND CUNT WHYyyyy\n");
		return (0);
	}
	list_update(node, input_d);
	printf("Dest: %s->%s\n", (*input_d)->dest->name, ((*input_d)->dest->next) ? (*input_d)->dest->next->name : "NULL");
	printf("Start forcing direction\n");
	forward_direction((*input_d)->dest);
	// // sum_paths(node, input_d, 1); // Boolean trigger make directional
	printf("\n========== 2nd OP =========\n");
	printf("Optimal path to |\"%s\"|", (*input_d)->dest->name);
	printf(" (%d)\n", backwards_node_weight((*input_d)->dest));
	optimal = (*input_d)->dest->path;
	while (optimal)
	{
		printf("%s\n", optimal->name);
		optimal = optimal->path;
	}
	return (1);
}