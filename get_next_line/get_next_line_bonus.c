/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mande-so <mande-so@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 23:20:06 by mande-so          #+#    #+#             */
/*   Updated: 2025/12/04 23:14:09 by mande-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	buffer[OPEN_MAX][BUFFER_SIZE + 1];
	char		*line;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	if (read(fd, 0, 0) < 0)
		return (*buffer[fd] = '\0', NULL);
	while (1)
	{
		if (!*buffer[fd])
			ft_fillbuf(fd, buffer[fd]);
		if (!*buffer[fd])
			break ;
		line = ft_strjoin(line, buffer[fd]);
		if (!line)
			return (*buffer[fd] = '\0', NULL);
		if (ft_findnl(buffer[fd]))
			return (ft_shiftbuf(buffer[fd]), line);
		*buffer[fd] = '\0';
	}
	if (!line || !*line)
		return (free(line), NULL);
	return (line);
}
