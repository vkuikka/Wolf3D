# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkuikka <vkuikka@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/08 13:46:11 by vkuikka           #+#    #+#              #
#    Updated: 2020/01/13 21:22:02 by vkuikka          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Wolf3D
#LIBFT = libft/libft.a
FILES = main.c
#FDF = -I /usr/local/include -L /usr/local/lib -lmlx -framework OpenGL -framework Appkit
INCLUDE = libft/includes
.PHONY: clean fclean re all


LIBFT = libft/libft.a ~/Documents/github/minilibx/libmlx_Linux.a
FDF = -I ~/Documents/github/minilibx -lXext -lX11 -lm

all: $(NAME)

$(NAME):
	gcc -o $(NAME) -Wall -Wextra -Werror $(FILES) $(LIBFT) -I $(INCLUDE) $(FDF)
	#@make -C libft

clean:
	#@make clean -C libft

fclean: clean
	rm -f $(NAME)
	#@make fclean -C libft

re: fclean
	make all
