# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: fholwerd <fholwerd@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/11/08 15:59:07 by fholwerd      #+#    #+#                  #
#    Updated: 2023/05/25 20:10:28 by fholwerd      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D
SRC		= src/main.c \
			src/cub3d.c \
			src/stop.c \
			src/parser/colours.c \
			src/parser/errors.c \
			src/parser/errors2.c \
			src/parser/find_map.c \
			src/parser/file_checker.c \
			src/parser/initialize.c \
			src/parser/map_dimensions.c \
			src/parser/parse_map.c \
			src/parser/parse_textures.c \
			src/parser/parser.c \
			src/parser/parse_utils/ft_atoi.c \
			src/parser/parse_utils/ft_instring.c \
			src/parser/parse_utils/ft_memchr.c \
			src/parser/parse_utils/ft_split.c \
			src/parser/parse_utils/ft_strchr.c \
			src/parser/parse_utils/ft_strcmp.c \
			src/parser/parse_utils/ft_strdup.c \
			src/parser/parse_utils/ft_strjoin.c \
			src/parser/parse_utils/ft_strlen.c \
			src/parser/parse_utils/ft_strncmp.c \
			src/parser/parse_utils/ft_strrchr.c \
			src/parser/parse_utils/ft_substr.c \
			src/parser/parse_utils/get_next_line.c \
			src/parser/parse_utils/get_next_line_utils.c \
			src/raycaster/draw_walls.c \
			src/raycaster/init_raycaster.c \
			src/raycaster/minimap.c \
			src/raycaster/movement.c \
			src/raycaster/raycaster.c \
			src/raycaster/utils/correct_color.c \
			src/raycaster/utils/deg_to_rad.c \
			src/raycaster/utils/draw_line.c \
			src/raycaster/utils/draw_rectangle.c \
			src/raycaster/utils/fix_ang.c \
			src/raycaster/utils/image_to_window.c \
			src/raycaster/utils/init_image.c \
			src/raycaster/utils/load_texture.c \
			src/raycaster/utils/point.c \
			src/raycaster/utils/put_pixel.c \
			src/raycaster/utils/rectangle.c \
			src/raycaster/utils/set_background.c
OBJ		= $(SRC:.c=.o)
INCLUDE	= -I include \
		  -I include/parser \
		  -I include/parser/parse_utils \
		  -I include/raycaster \
		  -I include/raycaster/utils \
		  -I MLX42/include/MLX42
LINKS	= 
CFLAGS	= -Wall -Wextra -Werror -O2 #-g -fsanitize=address
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
	@cmake -S $(MLXDIR) -B $(MLXDIR)build
	@make -C $(MLXDIR)build

clean:
	@echo "Cleaning files."
	@rm -f $(OBJ)
	@rm -f $(ALEX_SRC:.c=.o)
	@rm -f $(FRANS_SRC:.c=.o)

fclean: clean
	@echo "Cleaning executable."
	@rm -f $(NAME)
	@echo "Cleaning MLX library."
	@rm -rf $(MLXDIR)build

re: fclean all

.PHONY: all clean fclean re
