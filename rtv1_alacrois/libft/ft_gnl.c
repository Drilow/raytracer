/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <alacrois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/05 19:32:25 by alacrois          #+#    #+#             */
/*   Updated: 2017/10/23 16:11:57 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			find_line(int const fd, char *buff, size_t *len, char **l)
{
	size_t	i;
	int		read_return;

	i = 0;
	if (buff[0] == '\0')
	{
		read_return = read(fd, buff, BUFF_SIZE);
		if (read_return < 1)
			return (read_return);
	}
	while (buff[i] != '\n' && buff[i] != '\0')
		i++;
	*len = i;
	*l = (char *)malloc(sizeof(char) * (*len + 1));
	if (*l == NULL)
		return (-1);
	return (1);
}

static void			update_buffer(char *buff, size_t len)
{
	size_t	index;

	index = 0;
	while ((index + len < BUFF_SIZE) && (buff[index + len] != '\0'))
	{
		buff[index] = buff[index + len];
		index++;
	}
	while (index < BUFF_SIZE)
	{
		buff[index] = '\0';
		index++;
	}
}

static int			save_line(int const fd, char *buff, char **line)
{
	size_t	len;
	int		find_return;
	char	*new_line;
	char	*next_line;

	*line = NULL;
	find_return = find_line(fd, buff, &len, &new_line);
	if (find_return != 1)
		return (find_return);
	new_line = ft_strncpy(new_line, buff, len);
	new_line[len] = '\0';
	if (buff[len] == '\0')
	{
		update_buffer(buff, len + 1);
		if (save_line(fd, buff, &next_line) == -1)
			return (-1);
		*line = ft_strjoin(new_line, next_line);
		free(new_line);
		free(next_line);
		return (1);
	}
	update_buffer(buff, len + 1);
	*line = new_line;
	return (1);
}

static t_bufflist	*get_buffer(int const fd, t_bufflist *first_buff)
{
	t_bufflist		*tmp;
	t_bufflist		*new_elem;

	if (fd == first_buff->fd)
		return (first_buff);
	tmp = first_buff;
	while (tmp->next != NULL && tmp->fd != fd)
		tmp = tmp->next;
	if (tmp->fd != fd)
	{
		new_elem = (t_bufflist *)malloc(sizeof(t_bufflist));
		if (new_elem == NULL)
			return (NULL);
		new_elem->buffer[BUFF_SIZE] = '\0';
		update_buffer(new_elem->buffer, BUFF_SIZE);
		if (read(fd, new_elem->buffer, BUFF_SIZE) == -1)
			return (NULL);
		new_elem->fd = fd;
		new_elem->next = NULL;
		tmp->next = new_elem;
	}
	else
		new_elem = tmp;
	return (new_elem);
}

int					ft_gnl(int const fd, char **line)
{
	static t_bufflist	f_buff[1];
	t_bufflist			*new_buff;

	if (f_buff->buffer[BUFF_SIZE] != '\0' && fd != -1 && line != NULL)
	{
		f_buff->buffer[BUFF_SIZE] = '\0';
		f_buff->fd = fd;
		f_buff->next = NULL;
		update_buffer(f_buff->buffer, BUFF_SIZE);
		if (read(fd, f_buff->buffer, BUFF_SIZE) == -1)
			return (-1);
	}
	if ((line == NULL) || (fd == -1))
		return (-1);
	new_buff = get_buffer(fd, f_buff);
	if (new_buff == NULL)
		return (-1);
	return (save_line(fd, new_buff->buffer, line));
}
