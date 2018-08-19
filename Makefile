NAME = mod1
CC = gcc
CFLAGS = -O2 -Wall -Wextra -Werror
SRC = control.c fill.c landscape.c main.c moses.c rain.c read.c refresh.c screen.c snow.c support.c
OBJ = $(SRC:.c=.o)

GRAPHICS = -framework OpenGL -framework AppKit -lpthread
MLX_LNK = -L ./minilibx_macos -lmlx
FT_LNK = -L ./libft -lft

$(NAME):
	@ulimit -s hard
	@$(CC) $(CFLAGS) $(MLX_LNK) $(GRAPHICS) $(FT_LNK) $(SRC) -o $(NAME)

all: $(NAME)

clean:
	@/bin/rm -f $(OBJ)

fclean: clean
	@/bin/rm -f $(NAME)

re:	fclean all
