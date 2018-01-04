/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 13:10:41 by asyed             #+#    #+#             */
/*   Updated: 2018/01/03 19:53:39 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdlib.h>
#include <stdio.h> //lol
#include <errno.h> //lol

int	comment_parse(char **line, int *start)
{
	if (!ft_strcmp(*line, "##start"))
	{
		*start = 1;
		return (1);
	}
	if (!ft_strcmp(*line, "##end"))
	{
		*start = 0;
		return (1);
	}
	printf("I'm a comment bitch: \"%s\"\n", *line);
	// free(*line);
	// *line = NULL;
	return (0);
}

int	skip_comments(char **line, int *start)
{
	if (*line)
		free(*line);
	while (get_next_line(0, line))
	{
		if (**line == '#' && comment_parse(line, start))
			return (0);
		else if (**line != '#')
			return (1);
		else
		{
			free(*line);
			*line = NULL;
		}
	}
	return (1);
}

// int	fill_rooms(t_input *input_d)
// {
// 	char	*line;
// 	char	**line_d;
// 	t_rooms	*s_room;

// 	while (get_next_line(0, &line))
// 	{
// 		input_d->rooms = ft_memalloc(sizeof(t_rooms));
// 		if (!input_d->rooms)
// 		{
// 			printf("Failed to ft_memalloc(input_d->rooms)\n");
// 			return (0);
// 		}
// 		line_d = ft_strsplit(line, ' ');
// 		input_d->rooms->name = (*line_d)++;
// 		input_d->rooms->x = ft_atoi((*line_d)++);
// 		input_d->rooms->y = ft_atoi((*line_d));
// 	}
// }

int	info_copy(char **str, t_rooms **n_room)
{
	char	*new;
	size_t	i;

	new = ft_strdup(*str);
	if (!new)
	{
		printf("Failed to ft_strdup(str)\n");
		return (0);
	}
	i = 0;
	if (new[i] && (new[i] == '#' || new[i] == 'L'))
	{
		free(new);
		new = NULL;
		return (0);
	}
	while (new[i])
	{
		if (new[i] == ' ')
			break ;
		i++;
	}
	if (i == ft_strlen(*str))
	{
		free(new);
		new = NULL;
		return (0);
	}
	new[i++] = '\0';
	(*n_room)->name = new;
	(*n_room)->x = ft_atoi(&(new[i]));
	i += (ft_nbrlen((*n_room)->x));
	(*n_room)->y = ft_atoi(&(new[i]));
	return (1);
	//Reallocate to the new smaller size (i)!!!;
}

int	new_room(t_input **input_d, char **line)
{
	t_rooms	*new;

	new = ft_memalloc(sizeof(t_rooms));
	if (!new)
	{
		printf("Failed to ft_memalloc(new)\n");
		return (0);
	}
	if (!info_copy(line, &new))
	{
		printf("Failed to info_copy(line, new)\n");
		free(new);
		new = NULL;
		return (0);
	}
	printf("\n======\nRoom Created!\nName = %s, X,Y: %d, %d\n======\n\n", new->name, new->x, new->y);
	if ((*input_d)->rooms)
		new->next = (*input_d)->rooms;
	(*input_d)->rooms = new; //Append it to the front!
	return (1);
}

int	parse_input(t_input **input_d)
{
	char *line;
	int	start; //Bool to determine if we hit the Start/End command(s)	

	start = 0;
	if (!skip_comments(&line, &start))
		return (0);
	(*input_d)->ants = ft_atoi(line);
	if (!(*input_d)->ants && *line != '0')
		return (0);
	skip_comments(&line, &start);
	if (ft_strcmp(line, "##start"))
		return (0);
	free(line);
	line = NULL;
	while (get_next_line(0, &line))
	{
		if (*line == '#')
		{
			if (comment_parse(&line, &start))
			{
				free(line);
				break ;
			}
		}
		else if (new_room(input_d, &line))
		{
			printf("Added new room!\n");
		}
		/*
		** Print all the rooms!
		*/
		else if (!ft_strcmp(line, "printall"))
		{
			t_rooms *itt;

			itt = (*input_d)->rooms;
			while (itt)
			{
				printf("======\nName = %s, X,Y: %d, %d\n======\n\n", itt->name, itt->x, itt->y);
				itt = itt->next;
			}
		}
		/*
		** End remove me.
		*/
		else
		{
			printf("Unexpected input: %s\n", line);
			free(line);
			line = NULL;
		}
	}
	// while (get_next_line(0, &line))
	// {
	// 	if (!new_room(input_d, &line))
	// 	{
	// 		printf("Error'd on fill_rooms()\n");
	// 		return (0);
	// 	}		
	// }
	return (1);
}

int	main(void)
{
	t_input	*input_d;

	input_d = ft_memalloc(sizeof(t_input));
	if (!input_d)
	{
		printf("Error: %s\n", strerror(errno));
		return (-1);
	}
	if (parse_input(&input_d))
	{
		// ..
	}
	else
		printf("Error\n"); //Change to ft_printf
	return (0);
}