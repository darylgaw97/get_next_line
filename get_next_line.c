/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgaw <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 21:51:44 by dgaw              #+#    #+#             */
/*   Updated: 2021/10/14 21:51:47 by dgaw             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int gnl_find_end(const char *str, size_t n);
static char *gnl_make_line(char *cache);

char *get_next_line(int fd)
{
    static char *cache;
    char *buffer;
    char *line;

    buffer = malloc(BUFFER_SIZE + 1);
    if(!cache)
    {
        cache = malloc(BUFFER_SIZE + 1);
        if (read(fd, cache, BUFFER_SIZE) == 0)
            return (NULL);
    }
    while (!(gnl_find_end(cache, BUFFER_SIZE)))
    {
        if (read(fd, buffer, BUFFER_SIZE) != 0)
            cache = ft_strjoin(cache, buffer);
        else
        {
            if (cache[0] == '\0')
                return (NULL);
            char *last = ft_strdup(cache);
            free (cache);
            return (last);
        }
    }
    line = gnl_make_line(cache);
    cache += ft_strlen(line);
    return (line);
}

static int gnl_find_end(const char *str, size_t n)
{
    size_t i;

    i = 0;
    while (i < n)
    {
        if (str[i] == '\n')
            return (1);
        i++;
    }
    return (0);
}

static char *gnl_make_line(char *cache)
{
    size_t i;
    char *line;

    i = 0;
    while (cache[i] != '\n')
        i++;
    line = malloc(i + 1);
    if (!line)
        return (NULL);
    i = 0;
    while (cache[i] != '\n')
    {
        line[i] = cache[i];
        i++;
    }
    line[i] = '\n';
    line[++i] = '\0';
    return (line);
}