/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 13:19:23 by asyed             #+#    #+#             */
/*   Updated: 2018/01/12 13:15:02 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LEM_IN_H
# define FT_LEM_IN_H
# include "libft/libft.h"
# include <limits.h>
# define INFINITY INT_MAX

typedef struct	s_links
{
	struct s_links	*prev;
	struct s_rooms	*end;
	int				weight;
	struct s_links	*next;
}				t_links;

typedef struct	s_rooms
{
	char			*name;
	int				x;
	int				y;
	struct s_rooms	*path;
	struct s_links	*to_link;
	struct s_rooms	*next;
}				t_rooms;

typedef struct	s_input
{
	int		ants;
	int		p;
	t_rooms	*origin;
	t_rooms	*rooms;
	t_rooms *dest;
}				t_input;

/*
** execution.c 
*/
t_rooms	*find_room(t_input **input_d, char *room_name);
int		new_link(t_input **input_d, char *line);
int		new_room(t_input **input_d, char *line);
int		p_comment(t_input **input_d, char *line);
int		print_all(t_input **input_d, char *line);
int		print_links(t_input **input_d, char *line);
int		p_command(t_input **input_d, char *line);

/*
** main.c 
*/
int	comment_parse(char *line);
int	total_ants(t_input **input_d);
int	parse_input(t_input **input_d);

/*
** room.c
*/
int		valid_room(char *str, t_rooms *new);
int		add_room(void **building, char *line);
t_rooms	*is_room(t_rooms *floor, char *room_name);

/*
** utils.c
*/
void	skip_char(char *str, int *i, char c);
int		word_c(char *str);
char	next_char(const char *str);
/*
** validation.c
*/
int	debug_print(t_input *input_d, char *line);
int	debug_print_links(t_input *input_d, char *line);
int	is_link(t_input *input_d, char *line);
int	is_comment(t_input *input_d, char *line);
int	is_command(t_input *input_d, char *line);
int	is_valid_room(t_input *input_d, char *line);

/*
** djkstra.c 
*/

int	path_weight(t_rooms *src, t_rooms *dest);
int	node_weight(t_rooms *node);
int	dijkstra(t_input **input_d);
int	neighbor_update(t_rooms *node, t_input **input_d);

/*
** Debug bullshit
*/
int	print_weight(t_input **input_d, char *line);
int	debug_weight(t_input *input_d, char *line);
int	debug_pathbuilder(t_input *input_d, char *line);
int	buildmeafuckingpath(t_input **input_d, char *line);

struct			s_syntax
{
	char	*op_name;
	int		(*match)(t_input *input_d, char *line);
	int		(*exec)(t_input **input_d, char *line);	
}				t_syntax;

#endif
