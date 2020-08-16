# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkuikka <vkuikka@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/08 13:46:11 by vkuikka           #+#    #+#              #
#    Updated: 2020/08/16 15:08:26 by vkuikka          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d
FILES = main.c buttons.c
LIB = libft/libft.a
INCLUDES = -I libft/include -I includes -I libft/includes -I SDL2/SDL2/include/SDL2 -I SDL2/SDL2_image/include/SDL2
LIBS = -lSDL2 -lSDL2_image -L SDL2/SDL2/lib -L SDL2/SDL2_image/lib
.PHONY: clean fclean re all

all: $(NAME)

$(NAME):
	gcc -Wall -Wextra -Werror $(INCLUDES) -o $(NAME) $(FILES) $(LIB) $(LIBS)
	@make -C libft

clean:
	@make clean -C libft

fclean: clean
	rm -f $(NAME)
	@make fclean -C libft

re: fclean
	make all
