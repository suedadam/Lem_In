/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 13:19:23 by asyed             #+#    #+#             */
/*   Updated: 2018/01/04 19:34:10 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LEM_IN_H
# define FT_LEM_IN_H
# include "libft/libft.h"

typedef struct	s_rooms
{
	char			*name;
	int				x;
	int				y;
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

int	new_room(t_input **input_d, char *line, int *op_i);
int	new_link(t_input **input_d, char *line, int *op_i);
int	total_ants(t_input **input_d, char *line, int *op_i);
int	choose_func(t_input **input_d, char *line, int *op_i);
int	comment_parse(char *line);

int	is_valid_room(t_input *input_d, char *line);
int	is_comment(t_input *input_d, char *line);
int	is_link(t_input *input_d, char *line);
int	is_command(t_input *input_d, char *line);

int p_comment(t_input **input_d, char *line, int *op_i);
int p_command(t_input **input_d, char *line, int *op_i);

//Remove this garbage
int		print_all(t_input **input_d, char *line, int *op_i);
int		debug_print(t_input *input_d, char *line);
//End garbage
struct			s_operations
{
	char	*op_name;	
	int		(*func)(t_input **input_d, char *line, int *op_i);	
}				t_operations;

struct			s_syntax
{
	char	*op_name;
	int		(*match)(t_input *input_d, char *line);
	int		(*exec)(t_input **input_d, char *line, int *op_i);	
}				t_syntax;

#endif
