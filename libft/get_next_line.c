/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/10 12:13:58 by cpays             #+#    #+#             */
/*   Updated: 2018/11/15 19:24:27 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*check_fd(t_list **tmp, int fd)
{
	t_list	*tmp2;

	tmp2 = *tmp;
	while (tmp2)
	{
		if (tmp2->content_size == (size_t)fd)
			return (tmp2);
		tmp2 = tmp2->next;
	}
	tmp2 = ft_lstnew(ft_strnew(0), fd);
	ft_lstadd(tmp, tmp2);
	return (tmp2);
}

void	ft_loop(int ret, char *buffer, t_list **tmp)
{
	char	*tmp2;

	buffer[ret] = '\0';
	tmp2 = (*tmp)->content;
	(*tmp)->content = ft_strjoin(tmp2, buffer);
	ft_strdel(&tmp2);
}

void	ft_get2(char **line, t_list **tmp)
{
	char	*tmp2;
	size_t	len;

	len = ft_strchr((*tmp)->content, '\n') - (char*)(*tmp)->content;
	*line = ft_strsub((*tmp)->content, 0, len);
	tmp2 = (*tmp)->content;
	(*tmp)->content = ft_strdup(ft_strchr((*tmp)->content, '\n') + 1);
	ft_strdel(&tmp2);
}

void	ft_lstfree(t_list **lst)
{
	free((*lst)->content);
	free(*lst);
	(*lst)->next = NULL;
}

int		get_next_line(const int fd, char **line)
{
	char			buffer[BUFF_SIZE + 1];
	int				ret;
	static t_list	*tmp;
	t_list			*tmp2;

	if (line == NULL)
		return (-1);
	tmp2 = check_fd(&tmp, fd);
	ret = 0;
	while ((ft_strchr(tmp2->content, '\n')) == NULL
		&& (ret = read(fd, buffer, BUFF_SIZE)) > 0)
		ft_loop(ret, buffer, &tmp2);
	if (ret == -1)
		return (-1);
	if (ret == 0 && ft_strchr(tmp2->content, '\n') == NULL)
	{
		*line = ft_strdup(tmp2->content);
		return (0);
	}
	ft_get2(line, &tmp2);
	return (1);
}
