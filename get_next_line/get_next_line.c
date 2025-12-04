/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mande-so <mande-so@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 17:09:55 by mande-so          #+#    #+#             */
/*   Updated: 2025/12/03 12:29:41 by mande-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	ssize_t		bytes;

	line = NULL;
	bytes = 0;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	while (*buffer || (bytes = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		if (bytes > 0)
			buffer[bytes] = '\0';
		if (!(line = ft_strjoin(line, buffer)))
			return (NULL);
		if (ft_findnl(buffer))
			return (ft_shiftbuf(buffer), line);
		*buffer = '\0';
	}
	if (!line || !*line)
		return (free(line), NULL);
	return (line);
}
