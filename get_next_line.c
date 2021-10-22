/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgaw <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 19:57:39 by dgaw              #+#    #+#             */
/*   Updated: 2021/10/22 11:53:51 by dgaw             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	gnl_find_end(char *cache);
static int	gnl_load_cache(char **ptr_cache, int fd);
static char	*gnl_make_line(char **ptr_cache);
static void	gnl_update_cache(char **ptr_cache, char *line);

char	*get_next_line(int fd)
{
	static char	*cache;
	char		*line;

	if (fd < 0)
		return (NULL);
	while (!gnl_find_end(cache))
	{
		if (!gnl_load_cache(&cache, fd))
		{
			line = gnl_make_line(&cache);
			gnl_update_cache(&cache, line);
			return (line);
		}
	}
	line = gnl_make_line(&cache);
	gnl_update_cache(&cache, line);
	return (line);
}

static int	gnl_find_end(char *cache)
{
	if (cache == NULL)
		return (0);
	while (*cache)
	{
		if (*cache++ == '\n')
			return (1);
	}
	return (0);
}

static int	gnl_load_cache(char **ptr_cache, int fd)
{
	char	*buffer;
	char	*temp;
	size_t	i;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE) + 1);
	if (buffer == NULL)
		return (0);
	if (*ptr_cache == NULL)
		*ptr_cache = ft_strdup("");
	i = read(fd, buffer, BUFFER_SIZE);
	if (i == 0)
	{
		free (buffer);
		return (0);
	}
	buffer[i] = '\0';
	temp = *ptr_cache;
	*ptr_cache = ft_strjoin(*ptr_cache, buffer);
	free(temp);
	free(buffer);
	return (1);
}

static char	*gnl_make_line(char **ptr_cache)
{
	char	*line;
	size_t	i;

	if (ptr_cache == NULL)
		return (NULL);
	if (*(*ptr_cache) == '\0')
	{
		free(*ptr_cache);
		return (NULL);
	}
	i = 0;
	while ((*ptr_cache)[i] != '\n' && (*ptr_cache)[i] != '\0')
		i++;
	if ((*ptr_cache)[i] == '\n')
		line = malloc(sizeof(char) * i + 2);
	else if ((*ptr_cache)[i] == '\0')
		line = malloc(sizeof(char) * i + 1);
	i = 0;
	while (*ptr_cache[i] != '\n' && *ptr_cache[i] != '\0')
	{
		line[i] = *ptr_cache[i];
		i++;
	}
	if (*ptr_cache[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static void	gnl_update_cache(char **ptr_cache, char *line)
{
	char	*temp;
	size_t	cache_len;
	size_t	line_len;

	if (*ptr_cache == NULL || line == NULL)
		return ;
	temp = *ptr_cache;
	cache_len = ft_strlen(*ptr_cache);
	line_len = ft_strlen(line);
	*ptr_cache = ft_substr(*ptr_cache, line_len, cache_len - line_len);
	free (temp);
}
