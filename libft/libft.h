/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 18:38:51 by aleau             #+#    #+#             */
/*   Updated: 2018/10/16 13:10:01 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include "../Libjson/includes/json.h"
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# define BUFF_SIZE 32
# define FD_MAX 1000

typedef unsigned int	t_uint;

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

void			*ft_memcpy(void *s1, const void *s2, size_t n);
char			*ft_strndup(const char *s1, size_t n);
void			*ft_memmove(void *s1, const void *s2, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s1);
char			*ft_strcpy(char *s1, const char *s2);
char			*ft_strncpy(char *s1, const char *s2, size_t n);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strncat(char *s1, const char *s2, size_t n);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strstr(const char *s1, const char *s2);
int				ft_toupper(int c);
int				ft_tolower(int c);
int				ft_isprint(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
void			*ft_memset(void *b, int c, size_t n);
void			ft_bzero(void *s, size_t n);
void			*ft_memccpy(void *s1, const void *s2, int c, size_t n);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
char			*ft_strnstr(const char *s1, const char *s2, size_t n);
int				ft_atoi(const char *str);
void			ft_putchar(int c);
void			ft_putendl(char const *s);
void			ft_putnbr(int n);
void			ft_putstr(char const *s);
void			ft_putchar_fd(int c, int fd);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr_fd(int n, int fd);
char			*ft_strtrim(char const *s);
void			ft_strclr(char *s);
void			*ft_memalloc(size_t size);
void			ft_memdel(void **ap);
void			ft_strdel(char **as);
char			*ft_strnew(size_t size);
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void(*f)(unsigned int, char *));
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char(*f)(unsigned int, char));
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_itoa(int n);
char			**ft_strsplit(char const *s, char c);
t_list			*ft_lstnew(void const *content, size_t content_size);
void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lstadd_end(t_list **alst, t_list *new);
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
int				ft_pow(int nb, int pw);
int				get_next_line(int fd, char **line);
t_uint			ft_isspace(char c);
t_uint			ft_is_base(char c, char *base);
int				ft_atoi_base(const char *str, int str_base);
int				ft_abs(int n);
double			ft_atof(const char *str);
int				check_bool(t_json_file *file);
int				check_null(t_json_file *file);
void			*ft_free(void *ptr);
char			*ft_readfile(int fd, char *path);
int				ft_is_double(t_json_file *file);
void			pass_spaces(t_json_file *file);
void			pass_items(t_json_file *f);
double			ft_powe(double nb);
char			*ft_strjoini(char const *s1, char const *s2,
				size_t i, size_t j);
char			*ft_strmerge(char *src, char *dest, size_t i, size_t j);
void			*ft_exit_object(t_json_value *val, t_json_object *obj);
void			*ft_exit_array(t_json_value *val, t_json_array *arr);

#endif
