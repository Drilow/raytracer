NAME	 = libjson.a
CC		 = gcc
CFLAGS	 = -Wall -Wextra -Werror
INCLUDE = -I./includes -I/../libft/
SRCS	 = 			json_fill_value.c \
					json_get_types.c \
					json_init.c \
					json_new_bool.c \
					json_new_number.c \
					json_new_object.c \
					json_new_array.c \
					json_new_string.c \
					json_new_value.c \
					json_free_value.c

OBJ =				$(SRCS:.c=.o)

RM		 =			rm -f

all:	$(NAME) $(OBJ)

$(NAME)		:		$(SRCS)
					@gcc $(CFLAGS) -c $(SRCS)
					@ar rc $(NAME) $(OBJ)
					@ranlib $(NAME)

clean		:
					@/bin/rm -f $(OBJ)

fclean		:		clean
					@/bin/rm -f $(NAME)
re:			fclean all

.PHONY: re clean fclean all bjr