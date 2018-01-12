/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 20:09:57 by asyed             #+#    #+#             */
/*   Updated: 2018/01/12 13:15:41 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdlib.h>

int	valid_room(char *str, t_rooms *new)
{
	int	i;

	if (word_c(str) != 3 || *str == 'L' || *str == '#')
	{
		printf("wtf\n");
		return (0);
	}
	i = ft_strclen(str, ' ');
	str[i++] = '\0';
	new->name = ft_strdup(str);
	new->x = ft_atoi(&(str[i]));
	if (!new->x && next_char(&(str[i++])) != '0')
	{
		printf("failed to copied over\n");
		return (0);
	}
	i += ft_strclen(&(str[i]), ' ');
	new->y = ft_atoi(&(str[i]));
	if (!new->y && next_char(&(str[i])) != '0')
	{
		printf("failed to copy over (%c)\n", str[i]);
		return (0);
	}
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

t_rooms	*is_room(t_rooms *floor, char *room_name)
{
	while (floor)
	{
		if (!ft_strcmp(floor->name, room_name))
			return floor;
		floor = floor->next;
	}
	return (NULL);
}