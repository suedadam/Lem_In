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
		// printf("(%s)%d += (%s)%d\n", tmp->name, weight, tmp->path->name, path_weight(tmp, tmp->path));
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
		// printf("(%s)%d += (%s)%d\n", tmp->path->name, weight, tmp->name, path_weight(tmp->path, tmp));
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
		printf("Finding link for paths\n");
		if (find_link(node, neighbors->end))
			neighbors->end->path = node;
		neighbors = neighbors->next;
	}
	printf(".......\n");
	neighbors = node->to_link;
	while (neighbors)
	{
		printf("update me bitch\n");
		neighbor_update(neighbors->end, input_d);
		printf("bitch got updated\n");
		neighbors = neighbors->next;
	}
	printf("huh\n");
	return (1);
}

int	neighbor_update(t_rooms *node, t_input **input_d)
{
	int		n_weight;
	t_links	*neighbors;

	printf("omg I got stuck on node weight\n");
	n_weight = node_weight(node);
	printf("got the node weight my dude\n");
	neighbors = node->to_link;
	while (neighbors)
	{
		printf("%s -> %s\n", node->name, neighbors->end->name);
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
			printf("(M:%s N:%s) %d > %d + %d\n", node->name, neighbors->end->name, ne_weight, n_weight, p_weight);
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
		printf("==========Next itteration!!!!=======\n");
		res = 0;
		tmp = (*input_d)->rooms;
		while (tmp)
		{
			// printf("Next neighbor(%s)\n", tmp->name);
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

t_links *last_link(t_links *links)
{
	while (links && links->next)
		links = links->next;
	return (links);
}

// int	del_lastl(t_links *links)
// {
// 	t_links	*tmp;

// 	tmp = links;
// 	while (tmp && tmp->prev->next)
// 		tmp = tmp->prev;
// 	printf("First = \"%s\"\n", tmp->end->name);
// 	if (!tmp)
// 	{
// 		printf("Failed del_lastl()\n");
// 		return (0);
// 	}
// 	tmp->prev = tmp->prev->prev;
// 	printf("del_lastl(->prev set to %s && prev = %s)\n", tmp->prev->end->name, last_link(links)->end->name);
// 	return (1);
// }

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

t_links	*find_link(t_rooms *src, t_rooms *node)
{
	t_links	*itt;

	itt = src->to_link;
	while (itt)
	{
		// printf("{FL; %s} (== %s)", src->name, node->name);
		// printf("-> %s (== %s)\n", itt->end->name, node->name);
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

int	create_link(t_rooms *src, t_rooms *dest, int weight)
{
	t_links	*new;

	new = ft_memalloc(sizeof(t_links));
	if (!new)
	{
		printf("Failed to malloc()\n");
		exit(1);
	}
	new->end = dest;
	if (!append_link(&(src->to_link), &new, weight))
	{
		printf("Failed to append!\n");
		exit(1);
	}
	return (1);
}

int	reverse_direction(t_rooms *dest)
{
	t_rooms	*optimal;
	t_links	*link;

	optimal = dest;
	while (optimal && optimal->path)
	{
		printf("lol\n");
		if (find_link(optimal->path, optimal))
		{
			printf("Deleting %s -> %s\n", optimal->path->name, optimal->name);
			if (!delete_link(&(optimal->path), &optimal))
			{
				printf("Failed to delete. %s -> %s\n", optimal->name, optimal->path->name);
				exit(1);
			}
		}
		printf("find_link()\n");
		if ((link = find_link(optimal, optimal->path)))
		{
			printf("Found link\n");
			link->weight = -link->weight;
		}
		else
		{
			if (!create_link(optimal, optimal->path, -1))
			{
				printf("Failed to create link!\n");
				exit(1);
			}
		}
		printf("done lol find\n");
		optimal = optimal->path;
	}
	printf("done reversal :D\n");
	return (1);
}

// int	reverse_direction(t_rooms *dest)
// {
// 	t_rooms	*optimal;

// 	optimal = dest;
// 	while (optimal && optimal->path)
// 	{
// 		if (!delete_link(&(optimal->path), &optimal))
// 		{
// 			printf("{reverse_direction} delete_link(err)\n");
// 			return (0);
// 		}
// 		if (!(inverse_weight(find_link(optimal, optimal->path))))
// 		{
// 			printf("{reverse_direction} Failed to inverse_weight(%s -> %s)\n", optimal->name, optimal->path->name);
// 			if (find_link(optimal, optimal->path))
// 			{
// 				printf("Why'd it fail? It exists...\n");
// 				return (0);
// 			}
// 			else
// 			{
// 				if (!create_link(optimal, optimal->path, -1))
// 				{
// 					printf("Failed to create it too :'(\n");
// 					return (0);
// 				}
// 				printf("Created the link :)\n");
// 				return (1);
// 			}
// 		}
// 		optimal = optimal->path;
// 	}
// 	return (1);
// }

int	forward_direction(t_rooms *dest)
{
	t_rooms	*optimal;

	optimal = dest;
	while (optimal && optimal->path)
	{
		if (!delete_link(&optimal, &(optimal->path)))
			return (0);
		optimal = optimal->path;
	}
	return (1);
}

t_rooms	*copy_solution(t_rooms *source)
{
	t_rooms	*dest;
	t_rooms	*new;
	t_rooms	*itt;
	t_rooms	*tmp;

	if (!(new = ft_memalloc(sizeof(t_rooms))))
		return (NULL);
	itt = new;
	dest = source;
	while (dest)
	{
		if (!(tmp = ft_memalloc(sizeof(t_rooms))))
			return (NULL);
		tmp->name = ft_strdup(dest->name);
		//Fuck x & y we don't use that shit.
		// tmp->path = dest->path;
		itt->path = tmp;
		itt = itt->path;
		dest = dest->path;
	}
	return (new->path);
}

/*
** Return a copy of the rooms we just inversed!
*/

t_rooms	*inverse_optimal(t_input **input_d)
{
	t_rooms *i_node;
	t_rooms	*copy;

	reverse_direction((*input_d)->dest);
	if (!(copy = copy_solution((*input_d)->dest)))
		return (NULL);
	printf("Done copying the solution\n");
	i_node = (*input_d)->rooms;
	while (i_node)
	{
		i_node->path = NULL;
		i_node = i_node->next;
	}
	(*input_d)->dest->path = NULL;
	return (copy);
}

/*
** One = prev -> curr
** Two = curr -> prev
*/
int	flatten_paths(t_input **input_d)
{
	t_rooms	*node;
	t_links	*one;
	t_links	*two;

	node = (*input_d)->dest;
	while (node)
	{
		if (node->path)
		{
			printf("Evaluating %s and %s\n", node->path->name, node->name);
			if (!(one = find_link(node->path, node)) || !(two = find_link(node, node->path)))
			{
				printf("Failed to find :'( \n");
				// return (0);
				node = node->path;
				continue;
			}
			if (one->weight > two->weight)
			{
				printf("DELETE ONE\n");
				delete_link(&(node->path), &node);
			}
			else if (two->weight > one->weight)
			{
				printf("DELETE TWO\n");
				delete_link(&node, &(node->path));
			}
			else
			{
				printf("{%s %s} DELETE EARTHHHHHHHHH %d == %d\n", node->name, node->path->name, one->weight, two->weight);
				delete_link(&(node->path), &node);
				delete_link(&node, &(node->path));
			}
		}
		// else
			//... continue...?
		node = node->path;
	}
	return (1);
}

int	del_lastl(t_links *link)
{
	while (link)
	{
		if (!link->prev->next)
			break ;
		link = link->prev;
	}
	if (!link)
	{
		printf("--------------NOOOOOOOOOOOOO\n");
		return (0);
	}
	link->prev = link->prev->prev;
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
			save = link;
			printf("Deleteing (%s -> %s)%p\n", (*node)->name, (*findme)->name, link);
			printf("{1} %p <- %p <- link = %p -> %p -> %p\n", link->prev->prev, link->prev, link, link->next, (link->next) ? link->next->next : NULL);
			if (link == (*node)->to_link)
			{
				if (link->prev == link)
				{
					free((*node)->to_link);
					(*node)->to_link = NULL;
					return (1);
				}
				printf("Repositioned\n");
				(*node)->to_link = link->prev;
				link = (*node)->to_link;
				if (save->next != link)
					link->next = save->next;
				else
					link->next = NULL;
				if (link->next)
					link->next->prev = link;
			}
			else
				link = link->prev;
			if (link->next)
				link->next = save->next;
			link->prev = save->prev;
			if (link->prev != link)
				link->prev->next = link;
			printf("{2} %p <- %p <- link = %p -> %p -> %p\n", link->prev->prev, link->prev, link, link->next, (link->next) ? link->next->next : NULL);
			free(save);
			return (1);
		}
		link = link->next;

		// if (link->end == *findme)
		// {
		// 	save = link;
		// 	printf("Deleting %p \n", link);
		// 	printf("{1} %p <- %p <- link = %p -> %p -> %p\n", link->prev->prev, link->prev, link, link->next, (link->next) ? link->next->next : NULL);
		// 	if (link == (*node)->to_link)
		// 	{
		// 		printf("bitch?\n");
		// 		if (link->prev != link)
		// 		{
		// 			printf("nooo %p != %p\n", link->prev, link);
		// 			(*node)->to_link = link->prev;
		// 		}
		// 		else
		// 		{
		// 			(*node)->to_link = NULL;
		// 			free(save);
		// 			return (1);
		// 		}
		// 	}
		// 	link = (*node)->to_link;
		// 	link->prev = save->prev;
		// 	link->next = save->next;
		// 	if (link->next)
		// 		link->next->prev = link;
		// 	// free(save);
		// 	printf("{2} %p <- %p <- link = %p -> %p -> %p\n", link->prev->prev, link->prev, link, link->next, (link->next) ? link->next->next : NULL);
		// 	return (1);
		// }
		// link = link->next;
	}
	return (0);
}

/*
** Two = Normal Direction; G -> H. Should be there :) Error if not.
** One = Reverse direction; H -> G.
*/
int	flat_paths(t_input **input_d)
{
	t_rooms	*node;
	t_links	*one;
	t_links	*two;

	node = (*input_d)->dest;
	while (node && node->path)
	{
		if (!(two = find_link(node->path, node)))
		{
			printf("Wtf cunt? (%s -> %s doesn't exist)\n", node->path->name, node->name);
			exit(1);
		}
		if ((one = find_link(node, node->path)))
		{
			if (one->weight + two->weight == 0)
			{
				printf("*******BYE BITCHHHHHHH******\n");
				//Error check these lmao.
				delete_link(&(node), &(node->path));
				delete_link(&(node->path), &(node));
			}
		}
		// printf("Deleting %s -> %s\n", node->name, node->path->name);
		// if (find_link(node, node->path))
		// {
		// 	if (!delete_link(&node, &(node->path)))
		// 	{
		// 		printf("Failed to delete!!! %s -> %s\n", node->name, node->path->name);
		// 		// return (0);
		// 		exit(1);
		// 	}
		// }
		node = node->path;
	}
	return (1);
}

// int	fix_direction(t_input **input_d, t_rooms *copy)
// {
// 	int		weight;
// 	t_links	*link;
// 	t_rooms	*dest;

// 	if (!copy)
// 		return (0);
// 	dest = (*input_d)->dest;
// 	while (copy)
// 	{

// 		dest = find_room(input_d, copy);
// 		// if (!(link = find_link(copy, copy->path)))
// 		// {
// 		// 	printf("Failed to find link?\n");
// 		// 	exit(1);
// 		// }
// 		// weight = link->weight;
// 		// if (!create_link(copy->path, copy, weight))
// 		// {
// 		// 	printf("Failed to create_link()\n");
// 		// 	exit(1);
// 		// }
// 		copy = copy->path;
// 	}
// 	return (1);
// }

int	bellman(t_input **input_d)
{
	t_rooms	*copy;
	// t_rooms *mani;

	if (!(copy = inverse_optimal(input_d)))
	{
		printf("You failed me sir.\n");
		return (0);
	}
	// printf("bitch fucker\n");
	if (!dij_start(input_d))
	{
		printf("Failed dij_start(2nd)\n");
		return (0);
	}
	// printf("what? :O \n");
	list_update(input_d);
	// fix_direction(copy);
	// mani = copy;
	// while (mani)
	// {
	// 	printf("{COPY} %s\n", mani->name);
	// 	mani = mani->path;
	// }
	// flat_paths(input_d);
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
	list_update(input_d);
	// if (!bellman(input_d))
	// {
	// 	printf("bellman failed me!\n");
	// 	return (0);
	// }
	printf("stuck at printing dest path!? \n");
	printf("{Printing Destination Path} (%d)\n", INFINITY);
	t_rooms *dpath;

	dpath = (*input_d)->dest;
	while (dpath)
	{
		if (dpath->path)
		{
			if (find_link(dpath->path, dpath))
				printf("%s\n", dpath->name);
			else
				printf("No path found from %s -> %s\n", dpath->path->name, dpath->name);
		}
		else if (dpath == (*input_d)->origin)
			printf("%s\n", dpath->name);
		else
			printf("Error!? No link from %s -> %s\n", (dpath->path) ? dpath->path->name : "NULL", dpath->name);
		dpath = dpath->path;
	}
	return (1);
}