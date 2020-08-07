# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkuikka <vkuikka@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/08 13:46:11 by vkuikka           #+#    #+#              #
#    Updated: 2020/08/07 20:21:03 by vkuikka          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d
FILES = main.c draw.c buttons.c
LIBFT = libft/libft.a
INCLUDE = libft/includes
SDL2 = -framework SDL2 -F $(FILES) -o ./$(NAME) -rpath 
SDL_EXEC = ./SDL2.framework/SDL2
.PHONY: clean fclean re all


MLX = -I /usr/local/include -L /usr/local/lib -lmlx -framework OpenGL -framework Appkit

#LIBFT = libft/libft.a ~/Documents/github/minilibx/libmlx_Linux.a
#FDF = -I ~/Documents/github/minilibx -lXext -lX11 -lm

all: $(NAME)

#clang++ -framework SDL2 -F ./Frameworks Source/main.cpp -o ./Output/main_test -rpath @executable_path/

$(NAME):
	#gcc -framework SDL2 -F ./Frameworks $(FILES) $(LIBFT) -I $(INCLUDE) -o ./Output/$(NAME) -rpath $(SDL_EXEC)
	gcc -o $(NAME) -Wall -Wextra -Werror $(FILES) $(LIBFT) -I $(INCLUDE) $(MLX)

	#@make -C libft

clean:
	#@make clean -C libft

fclean: clean
	rm -f $(NAME)
	#@make fclean -C libft

re: fclean
	make all
