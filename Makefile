# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: fholwerd <fholwerd@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/11/08 15:59:07 by fholwerd      #+#    #+#                  #
#    Updated: 2023/05/10 14:54:24 by fholwerd      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D
SRC		= src/main.c
OBJ		= $(SRC:.c=.o)
INCLUDE	= -I include \
		  -I include/parser \
		  -I include/raycaster \
		  -I include/utils \
		  -I MLX42/include/MLX42
LINKS	= 
CFLAGS	= -Wall -Wextra -Werror #-g -fsanitize=address
MLXFLAGS = -lglfw -L$(shell brew --prefix glfw)/lib -framework Cocoa -framework OpenGL -framework IOKit
MLXDIR = MLX42/
MLXLIB = $(MLXDIR)build/libmlx42.a
CC		= gcc

all: $(MLXLIB) $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

$(NAME): $(OBJ)
	@echo "Compiling executable."
	@$(CC) $(MLXLIB) $(MLXFLAGS) $(CFLAGS) $(OBJ) $(LINKS) -o $(NAME)

$(MLXLIB):
	@echo "Compiling MLX library."
	@make -C $(MLXDIR)build

clean:
	@echo "Cleaning files."
	@rm -f $(OBJ)
	@make -C $(MLXDIR)build clean

fclean: clean
	@echo "Cleaning executable."
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
