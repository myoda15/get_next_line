/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mande-so <mande-so@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 17:10:05 by mande-so          #+#    #+#             */
/*   Updated: 2025/12/12 17:42:57 by mande-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*join;
	int		i;
	int		j;

	join = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!join)
		return (free(s1), NULL);
	i = 0;
	while (s1 && s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		join[i++] = s2[j];
		if (s2[j++] == '\n')
			break ;
	}
	join[i] = '\0';
	free(s1);
	return (join);
}

int	ft_findnl(const char *buf)
{
	int	i;

	i = 0;
	while (buf && buf[i])
	{
		if (buf[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void	ft_shiftbuf(char *buf)
{
	int	i;
	int	j;

	i = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (buf[i] == '\n')
		i++;
	j = 0;
	while (buf[i])
		buf[j++] = buf[i++];
	buf[j] = '\0';
}

int	ft_fillbuf(int fd, char *buf)
{
	ssize_t	bytes;

	bytes = read(fd, buf, BUFFER_SIZE);
	if (bytes >= 0)
		buf[bytes] = '\0';
	else
		buf[0] = '\0';
	return (bytes);
}
