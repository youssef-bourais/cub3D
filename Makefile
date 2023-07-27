NAME = cub3D

FLAGS = -Wall -Wextra -Werror

CC = cc

mlx_lib = MLX42/libmlx42.a

DEPENDENCIES = -framework Cocoa -framework OpenGL -framework IOKit

glfw = $(shell brew --prefix glfw)

SRS = cub3d.c

all: $(NAME)

$(NAME): $(SRS) Makefile
	@$(CC) $(FLAGS) -o $(NAME) $(SRS) $(DEPENDENCIES) -lglfw -L"$(glfw)/lib" $(mlx_lib)
	@echo "cub3D compiled"

clean:
	@rm -f $(NAME)
	@echo "Object files cleaned"

run: $(NAME)
	@./$(NAME) map.cub
fclean: clean
	@rm -f $(NAME)
	@echo "Program Name cleaned"

re: fclean all

