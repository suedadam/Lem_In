/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 20:09:57 by asyed             #+#    #+#             */
/*   Updated: 2018/01/04 20:10:16 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	valid_room(char *str, t_rooms *new)
{
	int	i;
	int tmp;

	if (word_c(str) != 3 || *str == 'L' || *str == '#')
		return (0);
	i = ft_strclen(str, ' ');
	str[i++] = '\0';
	new->name = ft_strdup(str);
	skip_char(str, &i, ' ');
	tmp = ft_atoi(&(str[i]));
	if (!tmp && str[i] != '0')
		return (0);
	new->x = tmp;
	i += ft_nbrlen(tmp);
	skip_char(str, &i, ' ');
	tmp = ft_atoi(&(str[i]));
	if (!tmp && str[i] != '0')
		return (0);
	new->y = tmp;
	return (1);
}

int	add_room(void **building, char *line)
{
	t_rooms	*new;

	new = ft_memalloc(sizeof(t_rooms));
	if (!new)
	{
		printf("Error in ft_memalloc(new)\n");
		return (0);
	}
	if (!valid_room(line, new))
	{
		free(new);
		return (0);
	}
	if (*building)
		new->next = *building;
	*building = new;
	return (1);
}

int	is_room(t_rooms *floor, char *room_name)
{
	while (floor)
	{
		if (!ft_strcmp(floor->name, room_name))
			return (1);
		floor = floor->next;
	}
	return (0);
}