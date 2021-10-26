/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgaw <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 19:57:33 by dgaw              #+#    #+#             */
/*   Updated: 2021/10/19 19:57:35 by dgaw             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int main(int argc, char **argv)
{
    char *line;
    int fd;
    if (argc != 2 && argc != 3)
        return (1);


    fd = open("gnlTester/files/41_no_nl", O_RDONLY);
    fd = open("gnlTester/files/41_with_nl", O_RDONLY);
    fd = open("gnlTester/files/42_no_nl", O_RDONLY);
    fd = open("gnlTester/files/42_with_nl", O_RDONLY);
    fd = open("gnlTester/files/43_no_nl", O_RDONLY);
    fd = open("gnlTester/files/43_with_nl", O_RDONLY);
    fd = open("gnlTester/files/alternate_line_nl_no_nl", O_RDONLY);
    fd = open("gnlTester/files/alternate_line_nl_with_nl", O_RDONLY);
    fd = open("gnlTester/files/big_line_no_nl", O_RDONLY);
    fd = open("gnlTester/files/big_line_with_nl", O_RDONLY);
    fd = open("gnlTester/files/empty", O_RDONLY);
    fd = open("gnlTester/files/multiple_line_no_nl", O_RDONLY);
    fd = open("gnlTester/files/multiple_nlx5", O_RDONLY);
    fd = open("gnlTester/files/nl", O_RDONLY);

    //for (fd = 3; fd < 17; fd++)
    //{
    if (argc == 2)
        fd = atoi(argv[1]);
    else
        fd = atoi(argv[2]);
    line = get_next_line(fd);
    while (line)
    {
        printf("%s", line);
        free(line);
        line = get_next_line(fd);
    }
    //}
}