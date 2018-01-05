/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 20:11:00 by asyed             #+#    #+#             */
/*   Updated: 2018/01/04 20:11:09 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	skip_char(char *str, int *i, char c)
{
	while (str[*i] == c)
		(*i)++;
}

int	word_c(char *str)
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

