/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mande-so <mande-so@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:02:30 by mande-so          #+#    #+#             */
/*   Updated: 2025/11/19 00:53:07 by mande-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "get_next_line.h"

// Função auxiliar para mostrar resultado
void print_result(const char *expected, const char *got, const char *test_name)
{
    if ((expected == NULL && got == NULL) ||
        (expected && got && strcmp(expected, got) == 0))
        printf("✅ %s passou\n", test_name);
    else
        printf("❌ %s falhou (esperado: \"%s\" | obtido: \"%s\")\n",
               test_name,
               expected ? expected : "NULL",
               got ? got : "NULL");
}

int main(void)
{
    int fd;
    char *line;

    // === Teste 1: ficheiro normal ===
    fd = open("teste1.txt", O_RDONLY);
    line = get_next_line(fd);
    print_result("ola mundo\n", line, "Linha 1 de teste1.txt");
    free(line);

    line = get_next_line(fd);
    print_result("isto e um teste\n", line, "Linha 2 de teste1.txt");
    free(line);

    line = get_next_line(fd);
    print_result("adeus\n", line, "Linha 3 de teste1.txt");
    free(line);

    line = get_next_line(fd);
    print_result("42\n", line, "Linha 4 de teste1.txt");
    free(line);

    line = get_next_line(fd);
    print_result("fim\n", line, "Linha 5 de teste1.txt");
    free(line);

    line = get_next_line(fd);
    print_result(NULL, line, "EOF de teste1.txt");
    free(line);
    close(fd);

    // === Teste 2: ficheiro vazio ===
    fd = open("vazio.txt", O_RDONLY);
    line = get_next_line(fd);
    print_result(NULL, line, "Ficheiro vazio");
    free(line);
    close(fd);

    // === Teste 3: sem newline no fim ===
    fd = open("sem_newline.txt", O_RDONLY);
    line = get_next_line(fd);
    print_result("ultima linha sem newline", line, "Ficheiro sem newline");
    free(line);

    line = get_next_line(fd);
    print_result(NULL, line, "EOF de sem_newline.txt");
    free(line);
    close(fd);

    // === Teste 4: ficheiro grande ===
    fd = open("grande.txt", O_RDONLY);
    line = get_next_line(fd);
    print_result("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n",
                 line, "Linha 1 de grande.txt");
    free(line);

    line = get_next_line(fd);
    print_result("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb\n",
                 line, "Linha 2 de grande.txt");
    free(line);

    line = get_next_line(fd);
    print_result("cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc\n",
                 line, "Linha 3 de grande.txt");
    free(line);

    line = get_next_line(fd);
    print_result(NULL, line, "EOF de grande.txt");
    free(line);
    close(fd);

    // === Teste 5: múltiplos FDs ===
    int fd1 = open("teste1.txt", O_RDONLY);
    int fd2 = open("teste2.txt", O_RDONLY);

    line = get_next_line(fd1);
    print_result("ola mundo\n", line, "FD1 primeira linha");
    free(line);

    line = get_next_line(fd2);
    print_result("primeira linha do ficheiro 2\n", line, "FD2 primeira linha");
    free(line);

    close(fd1);
    close(fd2);

    return 0;
}
