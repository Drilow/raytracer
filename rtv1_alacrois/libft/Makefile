NAME = libft.a

SRCS = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_strlen.c ft_strdup.c ft_strcpy.c ft_strncpy.c ft_strcat.c ft_strncat.c ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strstr.c ft_strnstr.c ft_strcmp.c ft_strncmp.c ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c ft_memalloc.c ft_memdel.c ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c ft_strjoin.c ft_strtrim.c ft_strsplit.c ft_itoa.c ft_putchar.c ft_putstr.c ft_putendl.c ft_putnbr.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c ft_lstmap.c ft_lstcpyone.c ft_lstcpy.c ft_lstdupone.c ft_lstdup.c ft_lstlen.c ft_lstnewlst.c ft_lstaddend.c ft_lstnadd.c ft_lstelem.c ft_lstrev.c ft_lstswap.c ft_gnl.c ft_pntcmp.c ft_delta.c ft_deltasq.c ft_rotate_point.c ft_milisleep.c ft_intmin.c ft_intmax.c ft_abs.c ft_exit.c ftx_draw_point.c ftx_draw_line.c ftx_img_pixel_put.c ftx_img_draw_line.c ft_point.c ft_rgb.c ft_dabs.c ftx_img_clear.c ft_putstrs.c ft_putstr_free.c ft_strcat_free.c ft_strsub_free.c ft_strjoin_free.c ft_strins.c ft_strins_free.c ft_strstrlen.c ft_lstsort.c ft_lstprint.c ft_lstdelbycontent.c ft_getspaces.c ft_getdigit.c ft_ddelta.c ft_ddeltasq.c ftx_get_pix_color.c ft_malloc.c ft_solve_equation.c ft_rpoint_cmp.c

OBJS = $(SRCS:.c=.o)

FLAGS = -Wall -Wextra -Werror

CC = gcc $(FLAGS)

all : $(NAME)

$(NAME) : $(OBJS)
	@echo "ar rc $(NAME) (OBJS)"
	@ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

clean :
	@echo "rm -f $\(OBJS) *~ *#"
	@rm -f $(OBJS) *~ *#

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: clean fclean all re
