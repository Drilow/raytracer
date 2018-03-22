# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/15 16:49:08 by adleau            #+#    #+#              #
#    Updated: 2018/03/22 09:10:23 by adleau           ###   ########.fr        #
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

LDFLAGS = `ext/SDL2/bin/sdl2-config --cflags --libs -lSDL2 -lSDL2_image`

LIB	 :=  -L./ext/SDL2/lib -I./ext/SDL2/include/SDL2
LIB	 += -L./ext/SDL2_Image/lib -I./ext/SDL2_Image/include/SDL2
#LIB	 += -L./ext/SDL2_ttf/lib -I./ext/SDL2_ttf/include/SDL2
LIB	 += -lSDL2 -lSDL2_image

#LIB_PATH  =  '/home/baarg/Desktop/new_SDL/ext/SDL2_Image/lib'
#LIB_PATH += ':/home/baarg/Desktop/new_SDL/ext/SDL2_ttf/lib'
#LIB_PATH += ':/home/baarg/Desktop/new_SDL/ext/SDL2/lib'

SRCPATH = srcs/

SRC =   $(SRCPATH)main.c \

INCPATH	=	includes/

INC	=

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
		rm -fr ext/SDL2 ext/SDL2_Image ext/SDL_ttf
		rm -fr SDL2-2.0.7.tar.gz SDL2-2.0.7 ext/SDL2/junk
		rm -fr SDL2_image-2.0.2.tar.gz SDL2_image-2.0.2 ext/SDL2_Image/junk
#		rm -fr SDL2_ttf-2.0.12.tar.gz SDL2_ttf-2.0.12 ext/SDL2_ttf/junk
		@echo "$(JAUN)~> [ SDL2 folder cleaned. ]$(NCOL)"
		make fclean -C libft/
		@echo "$(JAUN)~> [ libft cleaned. ]$(NCOL)"

re: clean all

ext: ext/SDL2 ext/SDL2_Image #ext/SDL2_ttf
#ext: ext/SDL2_Image ext/SDL2_ttf

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

ext/SDL2_ttf:
		rm -fr ext/SDL2_ttf
		mkdir -p ext/SDL2_ttf/junk
		rm -fr SDL2_ttf-2.0.12.tar.gz SDL2_ttf-2.0.12
#		wget http://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.0.12.tar.gz
#		@echo "$(VERT)~> [ SDL_ttf library downloaded. ]$(NCOL)"
#		tar xf SDL2_ttf-2.0.12.tar.gz
#		( export SDL2_CONFIG='$(shell pwd)/ext/SDL2/bin/sdl2-config' \
#		&& cd SDL2_ttf-2.0.12 \
#		&& ./configure --prefix=$(shell pwd)/ext/SDL2_ttf/ \
#		&& $(MAKE) && $(MAKE) install );
#		@echo "$(VERT)~> [ SDL_ttf library set up. ]$(NCOL)"
#		mv -f SDL2_ttf-2.0.12.tar.gz SDL2_ttf-2.0.12 ext/SDL2_ttf/junk

.PHONY: clean all re fclean
