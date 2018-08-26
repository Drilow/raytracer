# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Dagnear <Dagnear@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/15 16:49:08 by adleau            #+#    #+#              #
#    Updated: 2018/08/26 18:21:03 by adleau           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NCOL=\x1b[0m
VERT=\x1b[32;01m
JAUN=\x1b[33;01m
ROUG =\x1b[31;01m
BLEU =\x1b[34;01m

NAME = rt

CC = gcc

CFLAGS = -Wall -Werror -Wextra -O3 $(shell pkg-config --cflags gtk+-3.0) #-g -fsanitize=address

LDFLAGS = 	-framework IOKit -framework CoreVideo $(shell pkg-config --libs gtk+-3.0)


SRCPATH = srcs/

SRC =   $(SRCPATH)main.c \
		$(SRCPATH)gtk/base_screen.c			\
		$(SRCPATH)gtk/main_screen.c			\
		$(SRCPATH)gtk/edit_view.c			\
		$(SRCPATH)gtk/init_variables.c		\
		$(SRCPATH)maths/transformations.c	\
		$(SRCPATH)maths/ft_solve_equation.c	\
		$(SRCPATH)maths/ft_delta.c			\
		$(SRCPATH)maths/ft_deltasq.c		\
		$(SRCPATH)parser/parsing_1.c		\
		$(SRCPATH)parser/parsing_2.c		\
		$(SRCPATH)parser/parsing_3.c		\
		$(SRCPATH)parser/parse_objects.c		\
		$(SRCPATH)parser/parse_obj_file.c		\
		$(SRCPATH)objects/camera.c		\
		$(SRCPATH)objects/plane.c		\
		$(SRCPATH)objects/sphere.c		\
		$(SRCPATH)objects/cone_1.c		\
		$(SRCPATH)objects/cone_2.c		\
		$(SRCPATH)objects/cylinder_1.c		\
		$(SRCPATH)objects/cylinder_2.c		\
		$(SRCPATH)extra/ft_rgb.c		\
		$(SRCPATH)geometry/rpoint_fcts.c	\
		$(SRCPATH)maths/vector_fcts_1.c	\
		$(SRCPATH)maths/vector_fcts_2.c	\
		$(SRCPATH)display/display.c 	\
		$(SRCPATH)display/antialiasing.c \
		$(SRCPATH)raytracing/raytracing.c 	\
		$(SRCPATH)raytracing/colors.c 	\
		$(SRCPATH)gtk/draw_px.c 	\
		$(SRCPATH)raytracing/collision/normal_collision_vector.c 	\
		$(SRCPATH)raytracing/collision/obj_collision.c 	\

INCPATH	=	includes/

INC	=		$(INCPATH)objects/object.h \

OBJ = $(SRC:.c=.o)

all: $(NAME)


$(NAME): $(OBJ) $(INC)
		make -C libft/
		@echo "$(VERT)~> [ libft library made. ]$(NCOL)"
		$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -Iincludes/ $(LDFLAGS) -Ilibft/ -Llibft/ -lft $(LIB)
		@echo "$(VERT)~> [ binary file '$(NAME)' made. ]$(NCOL)"

%.o: %.c
		$(CC) $(CFLAGS) $(LDLAGS) -o  $@ -c $< -Ilibft/ -Iincludes/ $(LIB) -Qunused-arguments

clean:
		rm -rf $(OBJ)
		@echo "$(JAUN)~> [ .o files erased. ]$(NCOL)"
		make clean -C libft/

fclean: clean
		rm -f $(NAME)
		@echo "$(JAUN)~> [ binary file '$(NAME)' erased. ]$(NCOL)"
		rm -fr ext
		rm -fr ext/glfw
		rm -fr ext/glew
		rm -fr ext/SDL2
		rm -fr ext/SDL2_Image
		@echo "$(JAUN)~> [ glfw3 folder cleaned. ]$(NCOL)"
		make fclean -C libft/
		@echo "$(JAUN)~> [ libft cleaned. ]$(NCOL)"

re: fclean all

.PHONY: clean all re fclean
