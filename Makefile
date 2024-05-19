NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

<<<<<<< HEAD
LIBFT = libft/libft.a
FTPRINTF = libft/libftprintf.a
# MLX42 = libft/libmlx42.a -Iinclude -lglfw -L"/opt/homebrew/Cellar/glfw/3.3.9/lib/" -framework Cocoa -framework OpenGL -framework IOKit
MLX42 = /home/amura/Desktop/42Projects/so_long/MLX42/build/libmlx42.a -ldl -lglfw -pthread -lm
=======
LIBFT_DIR = libft
PRINTF_DIR = $(LIBFT_DIR)/printf

LIBFT = $(LIBFT_DIR)/libft.a
FTPRINTF = $(PRINTF_DIR)/libftprintf.a
MLX42 = MLX42/build/libmlx42.a -Iinclude -lglfw -L"/opt/homebrew/Cellar/glfw/3.3.9/lib/" -framework Cocoa -framework OpenGL -framework IOKit
>>>>>>> b07945d (changes)

SRC = main.c validate_map.c map_utils.c map_structure.c move.c resoudre.c resoudre2.c
OBJ = $(SRC:.c=.o)

all: $(LIBFT) $(FTPRINTF) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(FTPRINTF):
	$(MAKE) -C $(PRINTF_DIR)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(FTPRINTF) $(MLX42)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean
	$(MAKE) all
	$(MAKE) clean
	clear
	./so_long carte.ber