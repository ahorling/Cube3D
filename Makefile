# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: fholwerd <fholwerd@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/11/08 15:59:07 by fholwerd      #+#    #+#                  #
#    Updated: 2023/05/18 21:31:56 by ahorling      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D
SRC		= src/main.c \
			src/parser/errors.c \
			src/parser/file_checker.c \
			src/parser/initialize.c \
			src/parser/parser.c \
			src/parser/parse_utils/ft_strchr.c \
			src/parser/parse_utils/ft_strcmp.c \
			src/parser/parse_utils/ft_strjoin.c \
			src/parser/parse_utils/ft_strlen.c \
			src/parser/parse_utils/ft_strrchr.c \
			src/parser/parse_utils/get_lines.c \
			src/raycaster/minimap.c \
			src/raycaster/raycaster.c \
			src/utils/draw_line.c \
			src/utils/draw_rectangle.c \
			src/utils/point.c \
			src/utils/rectangle.c
OBJ		= $(SRC:.c=.o)
INCLUDE	= -I include \
		  -I include/parser \
		  -I include/parser/parse_utils \
		  -I include/raycaster \
		  -I include/utils \
		  -I MLX42/include/MLX42
LINKS	= 
CFLAGS	= #-Wall -Wextra -Werror #-g -fsanitize=address
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
	@rm -f $(ALEX_SRC:.c=.o)
	@rm -f $(FRANS_SRC:.c=.o)

fclean: clean
	@make -C $(MLXDIR)build clean
	@echo "Cleaning executable."
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
