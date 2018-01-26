/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 14:47:25 by asyed             #+#    #+#             */
/*   Updated: 2018/01/26 15:16:21 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
	char	*tmp;

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

int	move_join(char **str, t_rooms *rooms)
{
	char	*tmp;

	if (!(tmp = room_move(ft_itoa(rooms->ants), rooms->name)))
		return (0);
	if (!ft_strcat(*str, tmp))
		return (0);
	return (1);
}

int	push_ant(char **str, t_rooms *rooms, t_input **input_d)
{
	if (!str)
		return (0);
	if (!*str && !(*str = ft_memalloc(size_gen(input_d))))
		return (0);
	rooms->ants = rooms->path->ants;
	rooms->path->ants = 0;
	if (!move_join(str, rooms))
		return (0);
	ft_strcat(*str, " ");
	return (1);
}
