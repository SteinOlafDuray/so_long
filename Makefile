NAME = so_long
cc = GCC
RM = rm -f
INCLUDES = -I ./libft
FLAGS = -Wall -Wextra -Werror -g $(INCLUDES)
FRAMEWORKS = -lGL -lm -lXext -lX11
LIBFT_SRC = $(wildcard ./libft/*.c)

SRC = ./so_long.c \
	  ./p_draw.c \
	  ./parse.c \
	  ./parse2.c \
	  ./input.c \
	  ./utilize.c \
	  $(LIBFT_SRC) \
	#   ./gnl/get_next_line.c \
	#   ./gnl/get_next_line_utils.c \

MLX = ./libmlx.a \

OBJ = ${SRC:.c=.o}

.c.o:
	${CC} -c $< -o ${<:.c=.o}

${NAME}: ${OBJ}
	${CC} ${FLAGS} ${OBJ} ${MLX} -o ${NAME} ${FRAMEWORKS} 

all: ${NAME}

clean:
	${RM} ${OBJ} ${NAME}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY : all clean fclean re

