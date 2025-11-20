/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mande-so <mande-so@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 12:41:01 by mande-so          #+#    #+#             */
/*   Updated: 2025/11/19 10:18:19 by mande-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_file(int fd, char *storage)
{
	char	*buf;
	char	*temp;
	ssize_t	bytes;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	if (!storage)
		storage = ft_strdup("");
	bytes = 1;
	while (!ft_strchr(storage, '\n') && bytes > 0)
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes < 0)
			return (free(buf), free(storage), NULL);
		buf[bytes] = '\0';
		temp = ft_strjoin(storage, buf);
		storage = temp;
		if (!storage)
			return (free(buf), NULL);
	}
	free(buf);
	return (storage);
}

static char	*extract(char *storage)
{
	size_t	i;
	char	*line;

	if (!storage || !storage[0])
		return (NULL);
	i = 0;
	while (storage[i] && storage[i] != '\n')
		i++;
	if (storage[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	ft_strlcpy(line, storage, i + 1);
	return (line);
}

static char	*update(char *storage)
{
	size_t	i;
	char	*new;

	i = 0;
	while (storage[i] && storage[i] != '\n')
		i++;
	if (!storage[i])
		return (free(storage), NULL);
	i++;
	new = ft_strdup(storage + i);
	free(storage);
	return (new);
}


char	*get_next_line(int fd)
{
	static char	*storage;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	storage = read_file(fd, storage);
	if (!storage)
		return (NULL);
	line = extract(storage);
	storage = update(storage);
	return (line);
}
