/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgaw <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 19:57:39 by dgaw              #+#    #+#             */
/*   Updated: 2021/10/19 19:57:41 by dgaw             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int gnl_find_end(const char *cache);
static char *gnl_load_buffer(int fd);
static char *gnl_make_line(const char *cache);

char *get_next_line(int fd)
{
    static char *cache;
    char *buffer;
    char *temp;
    char *line;

    if (!cache)
        cache = ft_strdup("");
    while (!*cache || !gnl_find_end(cache))
    {
        temp = NULL;
        buffer = NULL;
        buffer = gnl_load_buffer(fd);
        if (!buffer)
        {
            if (*cache)
            {
                line = ft_strdup(cache);
                free(cache);
                cache = NULL;
                return (line);
            }
            else
            {
                free (cache);
                return (NULL);
            }
        }
        temp = cache;
        cache = ft_strjoin(cache, buffer);
        free(temp);
        free(buffer);
    }
    line = gnl_make_line(cache);
    temp = cache;
    cache = ft_substr(cache, ft_strlen(line), ft_strlen(cache) - ft_strlen(line));
    free(temp);
    return (line);
}

static int gnl_find_end(const char *cache)
{
    size_t i;

    i = 0;
    while (cache[i])
    {
        if (cache[i] == '\n')
            return (1);
        i++;
    }
    return (0);
}

static char *gnl_load_buffer(int fd)
{
    char *buffer;
    int i;

    buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!buffer)
        return (NULL);
    i = read(fd, buffer, BUFFER_SIZE);
    if (i == 0)
    {
        free(buffer);
        return (NULL);
    }
    buffer[i] = '\0';
    return (buffer);
}

static char *gnl_make_line(const char *cache)
{
    size_t i;
    char *line;

    i = 0;
    while (cache[i] != '\n')
        i++;
    line = malloc(sizeof(char) * (i + 2));
    i = 0;
    while (cache[i] != '\n')
    {
        line[i] = cache[i];
        i++;
    }
    line[i] = cache[i];
    line[++i] = '\0';
    return (line);
}