NAME = rtv1

SRCS =	main.c \
		parsing_1.c \
		parsing_2.c \
		parsing_3.c \
		parse_objects.c \
		parse_obj_file.c \
		transformations.c \
		events.c \
		display.c \
		ray_tracing.c \
		obj_collision.c \
		sphere_collision.c \
		plane_collision.c \
		cone_collision_1.c \
		cone_collision_2.c \
		cylinder_collision_1.c \
		cylinder_collision_2.c \
		light.c \
		normal_collision_vector.c \
		rpoint_fcts.c \
		vector_fcts_1.c \
		vector_fcts_2.c \
		misc.c

OBJS = $(SRCS:.c=.o)

FLAGS = -Wall -Wextra -Werror -Ofast

CC = gcc $(FLAGS)

all : $(NAME)

make_libft :
	@make -C libft

$(NAME) : make_libft $(OBJS)
	@gcc $(FLAGS) -o $(NAME) $(OBJS) -L libft -lft -lmlx -framework OpenGL -framework AppKit

clean :
	rm -f $(OBJS) *~ *#

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: clean fclean all re
