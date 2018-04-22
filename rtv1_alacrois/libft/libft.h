/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <alacrois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/22 16:48:25 by alacrois          #+#    #+#             */
/*   Updated: 2018/03/18 06:22:44 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <math.h>

# define BUFF_SIZE 32

typedef enum			e_bool
{
	true,
	false
}						t_bool;

typedef struct			s_list
{
	void				*content;
	size_t				content_size;
	struct s_list		*next;
}						t_list;

typedef struct			s_bufflist
{
	char				buffer[BUFF_SIZE + 1];
	int					fd;
	struct s_bufflist	*next;
}						t_bufflist;

typedef struct			s_point
{
	int					x;
	int					y;
}						t_point;

typedef struct			s_dpoint
{
	double				x;
	double				y;
}						t_dpoint;

typedef struct			s_3dpoint
{
	int					x;
	int					y;
	int					z;
}						t_3dpoint;

typedef struct			s_rpoint
{
	double				x;
	double				y;
	double				z;
}						t_rpoint;

typedef struct			s_rgb
{
	unsigned char		r;
	unsigned char		g;
	unsigned char		b;
	unsigned char		trans;
}						t_rgb;

typedef struct			s_img
{
	void				*img_p;
	char				*img_str;
	int					bpp;
	int					line_size;
	int					endian;
}						t_img;

typedef struct			s_env
{
	void				*mlx;
	void				*win;
	t_img				*i;
	void				*data;
}						t_env;

int						ft_intmax(int a, int b);
int						ft_intmin(int a, int b);
int						ft_abs(int n);
double					ft_dabs(double n);
void					ft_milisleep(int miliseconds);
void					ftx_draw_line(t_env *e, t_point a, t_point b, \
						int color);
void					ftx_draw_point(t_env *e, int x, int y, int color);
void					ftx_img_clear(t_img *img, int size_x, int size_y);
void					ftx_img_pixel_put(t_img *img, int x, int y, \
						t_rgb color);
t_rgb					ftx_get_pix_color(t_img *img, int x, int y);
void					ftx_img_draw_line(t_img *img, t_point a, \
						t_point b, t_rgb color);
t_rgb					ft_rgb(int r, int g, int b, int alpha);
double					ft_delta(t_point a, t_point b);
int						ft_deltasq(t_point a, t_point b);
double					ft_ddelta(t_dpoint a, t_dpoint b);
double					ft_ddeltasq(t_dpoint a, t_dpoint b);
t_point					ft_point(int x, int y);
int						ft_pntcmp(t_point a, t_point b);
void					ft_rotate_point(t_3dpoint *point, char axis, \
						double angle);
void					ft_exit(char *msg_error);

int						ft_gnl(int const fd, char **line);

void					*ft_memset(void *b, int c, size_t len);
void					ft_bzero(void *s, size_t n);
void					*ft_memcpy(void *dst, const void *src, size_t n);
void					*ft_memccpy(void *dst, const void *src, int c, \
						size_t n);
void					*ft_memmove(void *dst, const void *src, size_t len);
void					*ft_memchr(const void *s, int c, size_t n);
int						ft_memcmp(const void *s1, const void *s2, size_t n);
size_t					ft_strlen(char const *s);
size_t					ft_strstrlen(char const **s);
char					*ft_strdup(const char *s);
char					*ft_strcpy(char *dest, const char *src);
char					*ft_strncpy(char *dest, const char *src, size_t n);
char					*ft_strcat(char *s1, const char *s2);
char					*ft_strcat_free(char *s1, char *s2);
char					*ft_strncat(char *s1, const char *s2, size_t n);
size_t					ft_strlcat(char *dst, const char *src, size_t size);
char					*ft_strchr(const char *s, int c);
char					*ft_strrchr(const char *s, int c);
char					*ft_strstr(const char *s1, const char *s2);
char					*ft_strnstr(const char *s1, const char *s2, size_t n);
int						ft_strcmp(const char *s1, const char *s2);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
int						ft_atoi(const char *str);
int						ft_isalpha(int c);
int						ft_isdigit(int c);
int						ft_isalnum(int c);
int						ft_isascii(int c);
int						ft_isprint(int c);
int						ft_toupper(int c);
int						ft_tolower(int c);

void					*ft_memalloc(size_t size);
void					ft_memdel(void **ap);
char					*ft_strnew(size_t size);
void					ft_strdel(char **as);
void					ft_strclr(char *s);
void					ft_striter(char *s, void (*f)(char *));
void					ft_striteri(char *s, void (*f)(unsigned int, char *));
char					*ft_strmap(char const *s, char (*f)(char));
char					*ft_strmapi(char const *s, char (*f)(unsigned int, \
						char));
int						ft_strequ(char const *s1, char const *s2);
int						ft_strnequ(char const *s1, char const *s2, size_t n);
char					*ft_strsub(char const *s, unsigned int start, \
						size_t len);
char					*ft_strsub_free(char *s, unsigned int start, \
						size_t len);
char					*ft_strins(char *src, char *addon, int index);
char					*ft_strins_free(char *src, char *addon, int index);
char					*ft_strjoin(char const *s1, char const *s2);
char					*ft_strjoin_free(char *s1, char *s2);
char					*ft_strtrim(char const *s);
char					**ft_strsplit(char const *s, char c);
char					*ft_itoa(int n);
char					*ft_getspaces(int n);
int						ft_getdigit(int nb, int index);

void					ft_putchar(char c);
void					ft_putstr(char const *s);
void					ft_putstr_free(char *s);
void					ft_putstrs(char *s1, char *s2, char *s3, char *s4);
void					ft_putendl(char const *s);
void					ft_putnbr(int n);
void					ft_putchar_fd(char c, int fd);
void					ft_putstr_fd(char const *s, int fd);
void					ft_putendl_fd(char const *s, int fd);
void					ft_putnbr_fd(int n, int fd);

t_list					*ft_lstnew(void const *content, size_t content_size);
void					ft_lstdelone(t_list **alst, void (*del)(void *, \
						size_t));
void					ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void					ft_lstdelbycontent(t_list **l, char *content);
void					ft_lstadd(t_list **alst, t_list *new);
void					ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list					*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

t_list					*ft_lstcpyone(t_list *src);
t_list					*ft_lstcpy(t_list *src);
t_list					*ft_lstdupone(t_list *src);
t_list					*ft_lstdup(t_list *src);
size_t					ft_lstlen(t_list *lst);
t_list					*ft_lstnewlst(void *cont, size_t cont_size, \
						size_t l_size);
void					ft_lstaddend(t_list **alst, t_list *new);
void					ft_lstnadd(t_list **alst, t_list *new, size_t position);
t_list					*ft_lstelem(t_list *lst, size_t position);
void					ft_lstswap(t_list *elem1, t_list *elem2);
void					ft_lstrev(t_list *lst);
void					ft_lstsort(t_list *l);
void					ft_lstprint(t_list *l);

void					*ft_malloc(size_t size);
t_bool					ft_solve_equation(t_rpoint factors, t_dpoint *result);
t_bool					ft_rpoint_cmp(t_rpoint a, t_rpoint b);
#endif
