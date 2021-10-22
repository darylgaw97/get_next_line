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

static int  gnl_find_end(const char *cache);
static int  gnl_load_cache(char **cache, int fd);
static char *gnl_make_line(char *cache);
static void gnl_update_cache(char **caache, char *line);

char *get_next_line(int fd)
{
    static char *cache;
    char *line;

    if (cache == NULL)
        cache = ft_strdup("");
    while (!gnl_find_end(cache))
    {
        if (gnl_load_cache(&cache, fd) == 0)
        {
            if (*cache)
            {
                line = ft_strdup(cache);
                free(cache);
                return (line);
            }
            else
            {
                free(cache);
                return (NULL);
            }
        }
    }
    line = gnl_make_line(cache);
    gnl_update_cache(&cache, line);
    return (line);
}

static int gnl_find_end(const char *cache)
{
    while (*cache)
    {
        if (*cache++ == '\n')
            return (1);
    }
    return (0);
}

static int gnl_load_cache(char **cache, int fd)
{
    char *buffer;
    char *temp;
    int i;

    buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (buffer == NULL)
        return (0);
    i = read(fd, buffer, BUFFER_SIZE);
    if (i == 0)
        return (0);
    buffer[i] = '\0';
    temp = *cache;
    *cache = ft_strjoin(*cache, buffer);
    free(temp);
    return (1);
}

static char *gnl_make_line(char *cache)
{
    char *line;
    size_t i;

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
    line[i] = '\n';
    line[++i] = '\0';
    return (line);
}

static void gnl_update_cache(char **cache, char *line)
{
    char *temp;
    size_t cache_len;
    size_t line_len;

    temp = *cache;
    cache_len = ft_strlen(*cache);
    line_len = ft_strlen(line);
    *cache = ft_substr(*cache, line_len, cache_len - line_len);
    free(temp);
}