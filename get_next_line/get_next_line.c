/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mande-so <mande-so@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 17:09:55 by mande-so          #+#    #+#             */
/*   Updated: 2025/12/04 16:02:25 by mande-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	ssize_t		bytes;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	while (1)
	{
		if (!*buffer && (bytes = read(fd, buffer, BUFFER_SIZE)) > 0)
			buffer[bytes] = '\0';
		if (!*buffer)
			break ;
		line = ft_strjoin(line, buffer);
		if (!line)
			return (NULL);
		if (ft_findnl(buffer))
			return (ft_shiftbuf(buffer), line);
		*buffer = '\0';
	}
	if (!line || !*line)
		return (free(line), NULL);
	return (line);
}
