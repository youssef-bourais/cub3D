NAME = cub3D

FLAGS = -Wall -Wextra -Werror -fsanitize=address -g

CC = cc

mlx_lib = MLX42/libmlx42.a

DEPENDENCIES = -framework Cocoa -framework OpenGL -framework IOKit

glfw = $(shell brew --prefix glfw)

TOOLS = $(addprefix tools/, ft_split.c ft_strjoin.c ft_strncmp.c ft_strlen.c ft_strchr.c ft_strdup.c ft_substr.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_itoa.c ft_atoi.c)
PARS = $(addprefix parsing/, get_elems.c get_next_line.c get_next_line_utils.c)
SRS = cub3d.c $(PARS) $(TOOLS)

all: $(NAME)

$(NAME): $(SRS) Makefile
# @$(CC) $(FLAGS) -o $(NAME) $(SRS) $(DEPENDENCIES) -lglfw -L"$(glfw)/lib" $(mlx_lib)
	@$(CC) $(FLAGS) -o $(NAME) $(SRS)
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
