NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

LIBFT_DIR = libft
PRINTF_DIR = $(LIBFT_DIR)/printf

LIBFT = $(LIBFT_DIR)/libft.a
FTPRINTF = $(PRINTF_DIR)/libftprintf.a
MLX42_LINUX = MLX42/build/libmlx42.a -ldl -lglfw -pthread -lm
MLX42_MAC = MLX42/build/libmlx42.a -Iinclude -lglfw -L"/opt/homebrew/Cellar/glfw/3.3.9/lib/" -framework Cocoa -framework OpenGL -framework IOKit

SRC = main.c validate_map.c map_utils.c map_structure.c move.c resoudre.c resoudre2.c map_free.c
OBJ = $(SRC:.c=.o)

#change in CMakeLists.txt --> cmake_minimum_required (VERSION 3.16.0)

all: submodule mlx_build $(LIBFT) $(FTPRINTF) $(NAME)

linux :
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(FTPRINTF) $(MLX42_LINUX)

mac :
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(FTPRINTF) $(MLX42_MAC)

debug : all
	valgrind --keep-debuginfo=yes --show-leak-kinds=all --leak-check=full --suppressions=valgrind_files/mlx42.supp ./so_long test.ber

submodule :
	git submodule init
	git submodule update

mlx_build :
	sed -i 's/^cmake_minimum_required (VERSION 3.18.0)/cmake_minimum_required (VERSION 3.16.0)/g' MLX42/CMakeLists.txt
	cmake ./MLX42 -B ./MLX42/build
	cmake --build ./MLX42/build -j4

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(FTPRINTF):
	$(MAKE) -C $(PRINTF_DIR)

$(NAME): $(OBJ)
	$(MAKE) linux

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean
	$(MAKE) all
	$(MAKE) clean
	clear
	./so_long carte.ber