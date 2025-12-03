/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mande-so <mande-so@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:35:48 by mande-so          #+#    #+#             */
/*   Updated: 2025/12/02 11:38:32 by mande-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"
#include <fcntl.h>

int	main(void)
{
    int		fd;
    char	*line;

    fd = open("test.txt", O_RDONLY);
    if (fd < 0)
    {
        printf("Erro ao abrir ficheiro!\n");
        return (1);
    }
    
    while ((line = get_next_line(fd)))
    {
        printf("%s", line);
        free(line);
    }
    
    close(fd);
    return (0);
}
