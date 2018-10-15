/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readfile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 10:04:36 by mabessir          #+#    #+#             */
/*   Updated: 2018/10/15 11:49:56 by mabessir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_check(char *str)
{
	char *strr;

	if ((strr = ft_strstr(str, ".")) == NULL)
		return (0);
	if (ft_strncmp(strr, ".json", 5))
		return (0);
	return (1);
}

char	*ft_readfile(int fd, char *path)
{
	char			*str;
	int				ret;
	char			buf[4096 + 1];
	size_t			i;
	struct stat		buff;

	if ((stat(path, &buff)) == -1 || fd <= -1 || !ft_check(path))
		return (0);
	if ((buff.st_mode & S_IFREG) == 0)
		return (0);
	i = 0;
	str = ft_strnew(0);
	while ((ret = read(fd, buf, 1)) > 0)
	{
		buf[ret] = '\0';
		str = ft_strmerge(buf, str, ret, i);
		i += ret;
	}
	if (ret == -1)
	{
		ft_strdel(&str);
		return (0);
	}
	close(fd);
	return (str);
}
