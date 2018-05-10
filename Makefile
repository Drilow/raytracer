# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Dagnear <Dagnear@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/15 16:49:08 by adleau            #+#    #+#              #
#    Updated: 2018/05/10 12:19:04 by adleau           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NCOL=\x1b[0m
VERT=\x1b[32;01m
JAUN=\x1b[33;01m
ROUG =\x1b[31;01m
BLEU =\x1b[34;01m

NAME = rt

CC = gcc

CFLAGS = -Wall -Werror -Wextra -O3

LDFLAGS =  -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo -framework OpenCL
LDFLAGS += `ext/SDL2/bin/sdl2-config --cflags --libs -lSDL2`

LIB	 :=  -L./ext/SDL2/lib -I./ext/SDL2/include/SDL2


SRCPATH = srcs/

SRC =   $(SRCPATH)main.c \
		$(SRCPATH)maths/transformations.c	\
		$(SRCPATH)maths/ft_solve_equation.c	\
		$(SRCPATH)maths/ft_delta.c			\
		$(SRCPATH)maths/ft_deltasq.c		\
		$(SRCPATH)sdl_stuff/sdl_mgr.c		\
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
		$(SRCPATH)raytracing/raytracing.c 	\
		$(SRCPATH)raytracing/colors.c 	\
		$(SRCPATH)sdl_stuff/draw_px.c 	\
		$(SRCPATH)raytracing/collision/normal_collision_vector.c 	\
		$(SRCPATH)raytracing/collision/obj_collision.c 	\

INCPATH	=	includes/

INC	=		$(INCPATH)objects/object.h \
			$(INCPATH)sdl_stuff/sdl_mgr.h		\

OBJ = $(SRC:.c=.o)

all: ext $(NAME)

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

ext: ext/SDL2

ext/SDL2:
		rm -fr ext/SDL2
		mkdir -p ext/SDL2/junk
		rm -fr  SDL2-2.0.7
		curl -O http://www.libsdl.org/release/SDL2-2.0.7.tar.gz
		@echo "$(VERT)~> [ SDL library downloaded. ]$(NCOL)"
		tar xf SDL2-2.0.7.tar.gz
		( cd SDL2-2.0.7 \
		&& ./configure --prefix=$(shell pwd)/ext/SDL2/ \
		&& $(MAKE) && $(MAKE) install )
		mv -f SDL2-2.0.7.tar.gz SDL2-2.0.7 ext/SDL2/junk
		@echo "$(VERT)~> [ SDL library set up. ]$(NCOL)"

.PHONY: clean all re fclean
