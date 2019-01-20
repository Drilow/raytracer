# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alacrois <alacrois@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/15 16:49:08 by adleau            #+#    #+#              #
#    Updated: 2019/01/20 18:34:42 by alacrois         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NCOL=\x1b[0m
VERT=\x1b[32;01m
JAUN=\x1b[33;01m
ROUG =\x1b[31;01m
BLEU =\x1b[34;01m

NAME = rt

CC = gcc

CFLAGS = -Wall -Werror -Wextra -O3 $(shell pkg-config --cflags gtk+-3.0) -g3

LDFLAGS = 	-framework IOKit -framework CoreVideo $(shell pkg-config --libs gtk+-3.0)


SRCPATH = srcs/

SRC =   $(SRCPATH)main.c \
		$(SRCPATH)display/display.c 		\
		$(SRCPATH)display/antialiasing.c	\
		$(SRCPATH)extra/ft_rgb.c			\
		$(SRCPATH)geometry/rpoint_fcts.c	\
		$(SRCPATH)gtk/add_templates.c	 	\
		$(SRCPATH)gtk/base_screen.c			\
		$(SRCPATH)gtk/base_screen2.c		\
		$(SRCPATH)gtk/base_screen3.c		\
		$(SRCPATH)gtk/draw_px.c 			\
		$(SRCPATH)gtk/edit_base_view.c		\
		$(SRCPATH)gtk/edit_lights.c			\
		$(SRCPATH)gtk/edit_sphere.c			\
		$(SRCPATH)gtk/edit_view.c			\
		$(SRCPATH)gtk/edit_view2.c 			\
		$(SRCPATH)gtk/exit_properly.c		\
		$(SRCPATH)gtk/export_view.c			\
		$(SRCPATH)gtk/filter_functions.c	\
		$(SRCPATH)gtk/filter_view.c			\
		$(SRCPATH)gtk/gtk_handlers.c		\
		$(SRCPATH)gtk/gtk_handlers2.c		\
		$(SRCPATH)gtk/gtk_handlers3.c		\
		$(SRCPATH)gtk/init_light_view.c 	\
		$(SRCPATH)gtk/init_variables.c		\
		$(SRCPATH)gtk/key_events.c		 	\
		$(SRCPATH)gtk/main_screen.c			\
		$(SRCPATH)gtk/main_screen2.c		\
		$(SRCPATH)gtk/main_screen3.c		\
		$(SRCPATH)gtk/outline_obj.c			\
		$(SRCPATH)gtk/poly_view.c			\
		$(SRCPATH)gtk/progress_bar.c		\
		$(SRCPATH)gtk/radio_button.c		\
		$(SRCPATH)gtk/radio_toggle.c 		\
		$(SRCPATH)gtk/scene_view.c			\
		$(SRCPATH)gtk/scene_view2.c			\
		$(SRCPATH)gtk/validate_base_obj.c	\
		$(SRCPATH)gtk/validate_objects.c	\
		$(SRCPATH)gtk/validation.c			\
		$(SRCPATH)maths/ft_delta.c			\
		$(SRCPATH)maths/ft_deltasq.c		\
		$(SRCPATH)maths/ft_solve_equation.c	\
		$(SRCPATH)maths/transformations.c	\
		$(SRCPATH)maths/vector_fcts_1.c		\
		$(SRCPATH)maths/vector_fcts_2.c		\
		$(SRCPATH)objects/camera.c			\
		$(SRCPATH)objects/cone_1.c			\
		$(SRCPATH)objects/cone_2.c			\
		$(SRCPATH)objects/cylinder_1.c		\
		$(SRCPATH)objects/cylinder_2.c		\
		$(SRCPATH)objects/plane.c			\
		$(SRCPATH)objects/sphere.c			\
		$(SRCPATH)parser/get_tetrahedron.c	\
		$(SRCPATH)parser/get_cube.c			\
		$(SRCPATH)parser/get_cube_2.c		\
		$(SRCPATH)parser/objectsfn.c		\
		$(SRCPATH)parser/parsing_1.c		\
		$(SRCPATH)parser/parse_1.c			\
		$(SRCPATH)parser/parsing_2.c		\
		$(SRCPATH)parser/parsing_3.c		\
		$(SRCPATH)parser/parse_plane.c		\
		$(SRCPATH)parser/parse_sphere.c		\
		$(SRCPATH)parser/parse_pyra.c		\
		$(SRCPATH)parser/parse_camera.c		\
		$(SRCPATH)parser/parse_light.c		\
		$(SRCPATH)parser/parse_cone.c		\
		$(SRCPATH)parser/parse_cyl.c		\
		$(SRCPATH)parser/parse_amb_light.c	\
		$(SRCPATH)parser/parse_color.c		\
		$(SRCPATH)parser/parse_obj.c		\
		$(SRCPATH)parser/parse_objfile.c	\
		$(SRCPATH)parser/parse_cub.c		\
		$(SRCPATH)parser/parse_tetra.c		\
		$(SRCPATH)parser/parse_dodeca.c		\
		$(SRCPATH)parser/parse_obj_file_1.c	\
		$(SRCPATH)parser/parse_obj_file_2.c	\
		$(SRCPATH)parser/parse_obj_file_3.c	\
		$(SRCPATH)parser/set_obj.c			\
		$(SRCPATH)raytracing/collision/normal_collision_vector.c 	\
		$(SRCPATH)raytracing/collision/obj_collision.c				\
		$(SRCPATH)parser/get_dodecahedron_1.c	\
		$(SRCPATH)parser/get_dodecahedron_2.c	\
		$(SRCPATH)parser/po_malloc.c		\
		$(SRCPATH)parser/get_pyramid.c		\
		$(SRCPATH)raytracing/colors_1.c 	\
		$(SRCPATH)raytracing/colors_2.c 	\
		$(SRCPATH)raytracing/colors_3.c 	\
		$(SRCPATH)raytracing/raytracing_1.c \
		$(SRCPATH)raytracing/raytracing_2.c \
		$(SRCPATH)raytracing/raytracing_3.c \

INCPATH	=	includes/

INC	=		$(INCPATH)objects/object.h \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(INC)
		@echo "$(VERT)~> [ Sources compiled. ]$(NCOL)"
		@echo "$(JAUN)~> [ Compiling libft and Libjson. ]$(NCOL)"
		@make -C libft/
		@echo "$(VERT)~> [ libft compiled. ]$(NCOL)"
		@make -C Libjson/
		@echo "$(VERT)~> [ Libjson compiled. ]$(NCOL)"
		@echo "$(VERT)~> [ libft library made. ]$(NCOL)"
		@$(CC) $(CFLAGS) ./libft/libft.a ./Libjson/libjson.a $(OBJ) -o $(NAME) -Iincludes/ $(LDFLAGS) -Ilibft/ -I./Libjson/includes -Llibft/ -L./Libjson/ -lft $(LIB)
		@echo "$(VERT)~> [ binary file '$(NAME)' made. ]$(NCOL)"

%.o: %.c
		@echo "$(JAUN)~> [ Compiling sources, please wait. ]$(NCOL)"
		@$(CC) $(CFLAGS) $(LDLAGS) -o  $@ -c $< -Ilibft/ -ILibjson/includes -Iincludes/ $(LIB)

clean:
		@rm -rf $(OBJ)
		@echo "$(ROUG)~> [ .o files in project erased. ]$(NCOL)"
		@make clean -C libft/
		@echo "$(ROUG)~> [ .o files in libft erased. ]$(NCOL)"
		@make clean -C Libjson/
		@echo "$(ROUG)~> [ .o files in Libjson erased. ]$(NCOL)"

fclean: clean
		@rm -f $(NAME)
		@echo "$(ROUG)~> [ binary file '$(NAME)' erased. ]$(NCOL)"
		@make fclean -C libft/
		@echo "$(ROUG)~> [ libft cleaned. ]$(NCOL)"
		@make fclean -C Libjson/
		@echo "$(ROUG)~> [ Libjson cleaned. ]$(NCOL)"

re: fclean all

.PHONY: clean all re fclean
