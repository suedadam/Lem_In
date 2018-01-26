/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 13:19:23 by asyed             #+#    #+#             */
/*   Updated: 2018/01/26 15:31:46 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LEM_IN_H
# define FT_LEM_IN_H
# include "libft/libft.h"
# include <limits.h>
# include <stdlib.h>
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
	size_t			ants;
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
** weight.c
*/

int				node_weight(t_rooms *node);
int				path_weight(t_rooms *src, t_rooms *dest);
int				size_gen(t_input **input_d);

/*
** validation.c
*/

int				is_link(t_input *input_d, char *line);
int				find_not_num(const char *line, int length);
int				is_valid_room(t_input *input_d, char *line);
int				is_comment(t_input *input_d, char *line);
int				is_command(t_input *input_d, char *line);

/*
** utils.c
*/

void			skip_char(char *str, int *i, char c);
int				word_c(char *str);
char			next_char(const char *str);
char			*room_move(char *src, char *dst);
int				list_update(t_input **input_d);

/*
** room.c
*/

int				valid_room(char *str, t_rooms *new);
int				add_room(void **building, char *line);
t_rooms			*is_room(t_rooms *floor, char *room_name);
t_rooms			*find_room(t_input **input_d, char *room_name);

/*
** main.c
*/

int				comment_parse(char *line);
int				total_ants(t_input **input_d);
int				parse_input(t_input **input_d);
void			wrap_total_ants(t_input **input_d);

/*
** links.c
*/

t_links			*find_link(t_rooms *src, t_rooms *node);
int				del_lastl(t_rooms **node, t_links *link);
int				reposition_link(t_links *link, t_rooms **node);
int				delete_link(t_rooms **node, t_rooms **findme);
int				is_num(char *line);

/*
** execution.c
*/

int				append_link(t_links **src_links, t_links **new, int weight);
int				new_link(t_input **input_d, char *line);
int				new_room(t_input **input_d, char *line);
int				p_comment(t_input **input_d, char *line);
int				p_command(t_input **input_d, char *line);

/*
** djkstra.c
*/

int				dij_start(t_input **input_d);
int				neighbor_update(t_rooms *node, t_input **input_d);
int				min_neighbor(t_rooms *node, t_input **input_d);
char			*push_all(t_input **input_d);
int				dijkstra(t_input **input_d);

/*
** ants.c
*/

int				lost_ants(t_input **input_d);
int				push_ants(t_input **input_d);
int				push_ant(char **str, t_rooms *rooms, t_input **input_d);
int				move_join(char **str, t_rooms *rooms);

struct			s_syntax
{
	char	*op_name;
	int		(*match)(t_input *input_d, char *line);
	int		(*exec)(t_input **input_d, char *line);
}				t_syntax;

#endif
