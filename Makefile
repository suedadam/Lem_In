# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asyed <asyed@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/07 01:09:10 by asyed             #+#    #+#              #
#    Updated: 2018/01/04 20:06:49 by asyed            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem_in

CFLAGS += -Wall -Werror -Wextra -g

SRC = main.c \
		validation.c \
		utils.c \
		room.c \
		execution.c \

LIBFT = libft/

all: $(NAME)

$(NAME):
	@make -C $(LIBFT)
	@gcc $(CFLAGS) $(SRC) $(LIBFT)/libft.a -I $(LIBFT) -o $(NAME)
	@echo "\033[32mBuilt\033[0m"

clean:
	@/bin/rm -f $(NAME)
	@make clean -C $(LIBFT)
	@echo "\033[32mCleaned\033[0m"

fclean:
	@/bin/rm -f $(NAME)
	@/bin/rm -rf $(NAME).dSYM
	@make fclean -C $(LIBFT)
	@echo "\033[32mRemoved Executable\033[0m"
	@echo "\033[32mRemoved Symbol Bullshit\033[0m"
re: clean all
