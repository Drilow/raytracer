# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/15 16:49:08 by adleau            #+#    #+#              #
#    Updated: 2018/04/28 13:14:54 by adleau           ###   ########.fr        #
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

LIB	 :=  -L./ext/glfw/build/src/ -I./ext/glfw/include/GLFW/  -L./ext/glew/build/lib/ -I./ext/glew/include/ -I/usr/local/include -I/opt/X11/include -L/usr/local/lib -I/opt/X11/lib

SRCPATH = srcs/

SRC =   $(SRCPATH)main.c \
		$(SRCPATH)gl_handling/glfw_init.c \

INCPATH	=	includes/

INC	=		$(INCPATH)objects/object.h \
			$(INCPATH)gl_handling/gl_includes.h

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
		@echo "$(JAUN)~> [ glfw3 folder cleaned. ]$(NCOL)"
		make fclean -C libft/
		@echo "$(JAUN)~> [ libft cleaned. ]$(NCOL)"

re: fclean all

ext: ext/glfw ext/glew


ext/glfw:
		rm -fr ext/glfw
		git clone https://github.com/glfw/glfw.git ext/glfw
		@echo "$(VERT)~> [ glfw3 library downloaded. ]$(NCOL)"
		( cd ext/glfw && mkdir build && cd build \
		&& cmake ..  -DCMAKE_C_FLAGS="-Wno-deprecated" && make)
		#( cd ext/glfw && mkdir build && cd build \
		#&& $(HOME)/.brew/bin/cmake ..  -DCMAKE_C_FLAGS="-Wno-deprecated" && make)
		@echo "$(VERT)~> [ glfw3 library set up. ]$(NCOL)"

ext/glew:
		rm -fr ext/glew
		git clone https://github.com/nigels-com/glew.git ext/glew
		@echo "$(VERT)~> [ GLEW library downloaded. ]$(NCOL)"
		(cd ext/glew \
		&& $(MAKE) -C auto && cd build && cmake ./cmake  -DCMAKE_C_FLAGS="-Wno-deprecated" && make)
		#(cd ext/glew \
		#&& $(MAKE) -C auto && cd build && $(HOME)/.brew/bin/cmake ./cmake  -DCMAKE_C_FLAGS="-Wno-deprecated" && make)
		@echo "$(VERT)~> [ GLEW library set up. ]$(NCOL)"

.PHONY: clean all re fclean
