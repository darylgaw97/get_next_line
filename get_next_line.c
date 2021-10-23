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

static int		gnl_find_end(char *cache);
static int		gnl_load_cache(char **cache, int fd);
static char		*gnl_make_line(char *cache);
static void		gnl_update_cache(char **cache, char *line);

char *get_next_line(int fd)
{
	static char	*cache[MAX_FD];
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	while (gnl_find_end(cache[fd]) == -1)
	{
		if (!gnl_load_cache(&cache[fd], fd))
			break ;
	}
	line = gnl_make_line(cache[fd]);
	gnl_update_cache(&cache[fd], line);
	return (line);
}

static void	gnl_update_cache(char **cache, char *line)
{
	char	*temp;
	size_t	strlen_cache;
	size_t	strlen_line;

	if (*cache == NULL || **cache == '\0')
		return ;
	temp = *cache;
	strlen_cache = ft_strlen(*cache);
	strlen_line = ft_strlen(line);
	*cache = ft_substr(*cache, strlen_line, strlen_cache - strlen_line);
	free(temp);
	return ;
}

static char	*gnl_make_line(char *cache)
{
	char	*line;
	int		end;

	if (cache == NULL || *cache == '\0')
		return (NULL);
	end = gnl_find_end(cache);
	if (end >= 0)
		line = ft_substr(cache, 0, end + 1);
	else if (end == -1)
		line = ft_strdup(cache);
	return (line);
}

static int	gnl_load_cache(char **cache, int fd)
{
	char	*buffer;
	char	*temp;
	int		bytes_read;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (0);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
		return (0);
	buffer[bytes_read] = '\0';
	if (*cache == NULL)
		*cache = ft_strjoin(*cache, buffer);
	else if (*cache)
	{
		temp = *cache;
		*cache = ft_strjoin(*cache, buffer);
		free(temp);
	}
	free(buffer);
	return (1);
}

static int	gnl_find_end(char *cache)
{
	size_t i;

	if (cache == NULL)
		return (-1);
	i = 0;
	while (cache[i] != '\0')
	{
		if (cache[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}