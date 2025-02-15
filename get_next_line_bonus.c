/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 18:44:44 by tmoragli          #+#    #+#             */
/*   Updated: 2021/03/22 19:53:14 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s && s[i] != c && s[i])
		i++;
	if (s && c == s[i])
		return ((char *)(&s[i]));
	return (NULL);
}

int		ft_line(int fd, char **stock)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*temp;
	int		i;

	i = 0;
	buffer[0] = 0;
	while (!(ft_strchr(buffer, '\n')))
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i < 0)
			return (-1);
		buffer[i] = '\0';
		temp = *stock;
		*stock = ft_strjoin(*stock, buffer);
		free(temp);
		if (i < BUFFER_SIZE)
			return (0);
	}
	return (1);
}

int		get_next_line(int fd, char **line)
{
	static char		*stock[150];
	int				ret;
	char			*temp;

	temp = NULL;
	if (read(fd, temp, 0) < 0 || line == NULL || BUFFER_SIZE <= 0)
		return (-1);
	ret = 1;
	if (!ft_strchr(stock[fd], '\n'))
		ret = ft_line(fd, &stock[fd]);
	if (ret == 0 && !ft_strchr(stock[fd], '\n'))
		*line = ft_strdup(stock[fd]);
	else
	{
		ret = 1;
		*line = ft_substr(stock[fd], 0,
		(ft_strchr(stock[fd], '\n') - stock[fd]));
		temp = ft_strdup(ft_strchr(stock[fd], '\n') + 1);
	}
	free(stock[fd]);
	stock[fd] = temp;
	return (ret);
}
