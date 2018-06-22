# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Dagnear <Dagnear@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/15 16:49:08 by adleau            #+#    #+#              #
#    Updated: 2018/06/22 23:08:57 by alacrois         ###   ########.fr        #
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

LDFLAGS =  -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
LDFLAGS += `ext/SDL2/bin/sdl2-config --cflags --libs -lSDL2 -lSDL2_image`

LIB	 :=  -L./ext/glfw/build/src/ -I./ext/glfw/include/GLFW/  -L./ext/glew/build/lib/ -I./ext/glew/include/ -I/usr/local/include -I/opt/X11/include -L/usr/local/lib -I/opt/X11/lib
LIB	 +=  -L./ext/SDL2/lib -I./ext/SDL2/include/SDL2
LIB	 += -L./ext/SDL2_Image/lib -I./ext/SDL2_Image/include/SDL2
LIB	 += -lSDL2 -lSDL2_image


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
		$(SRCPATH)display/antialiasing.c \
		$(SRCPATH)raytracing/raytracing.c 	\
		$(SRCPATH)raytracing/colors.c 	\
		$(SRCPATH)sdl_stuff/draw_px.c 	\
		$(SRCPATH)raytracing/collision/normal_collision_vector.c 	\
		$(SRCPATH)raytracing/collision/obj_collision.c 	\

INCPATH	=	includes/

INC	=		$(INCPATH)objects/object.h \
			$(INCPATH)gl_handling/gl_includes.h \
			$(INCPATH)sdl_stuff/sdl_mgr.h		\

OBJ = $(SRC:.c=.o)

all: ext $(NAME)

$(NAME): $(OBJ) $(INC)
		make -C libft/
		@echo "$(VERT)~> [ libft library made. ]$(NCOL)"
		$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -Iincludes/ $(LDFLAGS) -Ilibft/ -Llibft/ -lft $(LIB) ./ext/glew/build/lib/libGLEW.a
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

ext: ext/glfw ext/glew ext/SDL2 ext/SDL2_Image


ext/glfw:
		rm -fr ext/glfw
		git clone https://github.com/glfw/glfw.git ext/glfw
		@echo "$(VERT)~> [ glfw3 library downloaded. ]$(NCOL)"
		#( cd ext/glfw && mkdir build && cd build \
		#&& cmake ..  -DCMAKE_C_FLAGS="-Wno-deprecated" && make)
		( cd ext/glfw && mkdir build && cd build \
		&& $(HOME)/.brew/bin/cmake ..  -DCMAKE_C_FLAGS="-Wno-deprecated" && make)
		@echo "$(VERT)~> [ glfw3 library set up. ]$(NCOL)"

ext/glew:
		rm -fr ext/glew
		git clone https://github.com/nigels-com/glew.git ext/glew
		@echo "$(VERT)~> [ GLEW library downloaded. ]$(NCOL)"
		#(cd ext/glew \
		#&& $(MAKE) -C auto && cd build && cmake ./cmake  -DCMAKE_C_FLAGS="-Wno-deprecated" && make)
		(cd ext/glew \
		&& $(MAKE) -C auto && cd build && $(HOME)/.brew/bin/cmake ./cmake  -DCMAKE_C_FLAGS="-Wno-deprecated" && make)
		@echo "$(VERT)~> [ GLEW library set up. ]$(NCOL)"

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

ext/SDL2_Image:
		rm -fr ext/SDL2_Image
		mkdir -p ext/SDL2_Image/junk
		rm -fr SDL2_image-2.0.2
		curl -O http://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.0.2.tar.gz
		@echo "$(VERT)~> [ SDL_Image library downloaded. ]$(NCOL)"
		tar xf SDL2_image-2.0.2.tar.gz
		( export SDL2_CONFIG='$(shell pwd)/ext/SDL2/bin/sdl2-config' \
		&& cd SDL2_image-2.0.2 \
		&& ./configure --prefix=$(shell pwd)/ext/SDL2_Image/ \
		&& $(MAKE) && $(MAKE) install );
		mv -f SDL2_image-2.0.2.tar.gz SDL2_image-2.0.2 ext/SDL2_Image/junk
		@echo "$(VERT)~> [ SDL_Image library set up. ]$(NCOL)"

.PHONY: clean all re fclean
