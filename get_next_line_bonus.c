/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qang <qang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 11:36:30 by qang              #+#    #+#             */
/*   Updated: 2023/05/23 12:25:40 by qang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*a_front(char *str)
{
	char	*temp;
	size_t	i;

	i = 0;
	if (!(*str))
		return (NULL);
	while (str[i] != '\n' && str[i])
		i++;
	temp = ft_calloc(i + 2, sizeof(char));
	if (!temp)
		return (NULL);
	i = 0;
	while (str[i] != '\n' && str[i])
	{
		temp[i] = str[i];
		i++;
	}
	temp[i] = str[i];
	return (temp);
}

char	*a_back(char *str)
{
	char	*temp;
	size_t	i;
	size_t	j;

	i = 0;
	while (str[i] != '\n' && str[i])
		i++;
	if (!(str[i]))
	{
		free(str);
		return (NULL);
	}
	j = ++i;
	while (str[i])
		i++;
	temp = ft_calloc(i - j + 1, sizeof(char));
	i = 0;
	while (str[j])
		temp[i++] = str[j++];
	free(str);
	return (temp);
}

char	*ft_read(char *a, int fd)
{
	char	*b;
	ssize_t	r;
	char	*temp;

	b = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!b)
		return (NULL);
	r = 1;
	while (r > 0)
	{
		r = read(fd, b, BUFFER_SIZE);
		if (r == -1)
		{
			free(b);
			return (NULL);
		}
		b[r] = '\0';
		temp = ft_strjoin(a, b);
		free(a);
		a = temp;
		if (ft_strchr(a, '\n'))
			break ;
	}
	free(b);
	return (a);
}

char	*get_next_line(int fd)
{
	static char	*a[10240];
	char		*b;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0))
		return (NULL);
	if (!(a[fd]))
		a[fd] = ft_calloc(1, sizeof(char));
	a[fd] = ft_read(a[fd], fd);
	b = a_front(a[fd]);
	a[fd] = a_back(a[fd]);
	return (b);
}
