# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkuikka <vkuikka@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/08 13:46:11 by vkuikka           #+#    #+#              #
#    Updated: 2020/08/15 17:14:26 by vkuikka          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d
FILES = main.c buttons.c ft_get_pixel.c
LIB = libft/libft.a
INCLUDES = -I libft/include -I includes -I libft/includes -I SDL2/SDL2/include/SDL2 -I SDL2/SDL2_image/include/SDL2
LIBS = -lSDL2 -lSDL2_image -L SDL2/SDL2/lib -L SDL2/SDL2_image/lib
.PHONY: clean fclean re all

all: $(NAME)

$(NAME):
	gcc $(INCLUDES) -o $(NAME) $(FILES) $(LIB) libft/libft.a $(LIBS)
	#gcc -Wall -Wextra -Werror -framework SDL2 -F ./ -framework SDL2_image -F ./ $(FILES) $(LIB) -I $(INCLUDE) -o $(NAME) -rpath @executable_path
	#@make -C libft

clean:
	#@make clean -C libft

fclean: clean
	rm -f $(NAME)
	#@make fclean -C libft

re: fclean
	make all
