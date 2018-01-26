/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 20:11:00 by asyed             #+#    #+#             */
/*   Updated: 2018/01/26 14:51:17 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	skip_char(char *str, int *i, char c)
{
	while (str[*i] == c)
		(*i)++;
}

int		word_c(char *str)
{
	int	i;

	i = 1;
	while (*str)
	{
		if (*str == ' ')
		{
			i++;
			while (*str && *str == ' ')
				str++;
		}
		else
			str++;
	}
	return (i);
}

char	next_char(const char *str)
{
	while (*str && (*str == ' ' || *str == '\t' || *str == '\r'
		|| *str == '\v' || *str == '\f'))
		str++;
	return (*str);
}

char	*room_move(char *src, char *dst)
{
	char	*str;

	if (!(str = ft_memalloc(ft_strlen(src) + ft_strlen(dst) + 2)))
		exit(1);
	str[0] = 'L';
	if (!(ft_strcat(str, src)))
		exit(1);
	str[ft_strlen(str)] = '-';
	if (!(ft_strcat(str, dst)))
		exit(1);
	return (str);
}

int		list_update(t_input **input_d)
{
	int		res;
	t_rooms	*tmp;

	res = 1;
	while (res)
	{
		res = 0;
		tmp = (*input_d)->rooms;
		while (tmp)
		{
			res += min_neighbor(tmp, input_d);
			tmp = tmp->next;
		}
	}
	return (1);
}
