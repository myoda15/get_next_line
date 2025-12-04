/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mande-so <mande-so@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 23:20:06 by mande-so          #+#    #+#             */
/*   Updated: 2025/12/04 10:34:14 by mande-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	buffer[OPEN_MAX][BUFFER_SIZE + 1];
	char		*line;
	ssize_t		bytes;

	line = NULL;
	bytes = 0;
	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (*buffer[fd] = '\0', NULL);
	while (*buffer[fd] || (bytes = read(fd, buffer[fd], BUFFER_SIZE)) > 0)
	{
		if (bytes > 0)
			buffer[fd][bytes] = '\0';
		if (!(line = ft_strjoin(line, buffer[fd])))
			return (NULL);
		if (ft_findnl(buffer[fd]))
			return (ft_shiftbuf(buffer[fd]), line);
		*buffer[fd] = '\0';
	}
	if (!line || !*line)
		return (free(line), NULL);
	return (line);
}
