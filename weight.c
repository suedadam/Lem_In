/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weight.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 14:45:43 by asyed             #+#    #+#             */
/*   Updated: 2018/01/26 14:48:52 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		path_weight(t_rooms *src, t_rooms *dest)
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

int		node_weight(t_rooms *node)
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
