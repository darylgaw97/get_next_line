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

int main(void)
{
    int fd;
    char *line;

    fd = open("oneline.txt", O_RDONLY);

    line = get_next_line(fd);
    while (line)
    {
        printf("%s", line);
        free (line);
        line = get_next_line(fd);
    }
}