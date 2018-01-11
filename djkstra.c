/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   djkstra.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 22:07:38 by asyed             #+#    #+#             */
/*   Updated: 2018/01/10 15:35:17 by asyed            ###   ########.fr       */
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
		weight += path_weight(tmp->path, tmp);
		tmp = tmp->path;
	}
	return (weight);
}

// int	dijkstra(t_input **input_d)
// {

// }