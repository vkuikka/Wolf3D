# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkuikka <vkuikka@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/08 13:46:11 by vkuikka           #+#    #+#              #
#    Updated: 2020/08/11 14:38:30 by vkuikka          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d
FILES = main.c buttons.c
LIB = libft/libft.a
INCLUDE = libft/includes
.PHONY: clean fclean re all

all: $(NAME)

$(NAME):
	gcc -Wall -Wextra -Werror -framework SDL2 -F ./ $(FILES) $(LIB) -I $(INCLUDE) -o $(NAME) -rpath @executable_path
	#@make -C libft

clean:
	#@make clean -C libft

fclean: clean
	rm -f $(NAME)
	#@make fclean -C libft

re: fclean
	make all
