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
static int	gnl_buffer(char **cache, int fd);
static char	*gnl_make_line(char *cache);
static void	gnl_update_cache(char **cache, char *line);

char	*get_next_line(int fd)
{
	static char	*cache[MAX_FD];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (!gnl_find_end(cache[fd]))
	{
		if (gnl_buffer(&cache[fd], fd) <= 0)
			break ;
	}
	line = gnl_make_line(cache[fd]);
	gnl_update_cache(&cache[fd], line);
	while (!gnl_find_end(cache[fd]))
	{
		if (gnl_buffer(&cache[fd], fd) <= 0)
			break ;
	}
	if (*cache[fd] == '\0')
	{
		free(cache[fd]);
		cache[fd] = NULL;
	}
	return (line);
}

void	gnl_update_cache(char **cache, char *line)
{
	char	*temp;
	size_t	strlen_cache;
	size_t	strlen_line;

	if (line == NULL)
		return ;
	strlen_cache = ft_strlen(*cache);
	strlen_line = ft_strlen(line);
	temp = *cache;
	*cache = ft_substr(*cache, strlen_line, strlen_cache - strlen_line);
	free(temp);
}

static char	*gnl_make_line(char *cache)
{
	char	*line;
	int 	i;

	if (cache == NULL)
		return (NULL);
	i = gnl_find_end(cache);
	if (i == -1)
		line = ft_strdup(cache);
	else
		line = ft_substr(cache, 0, i + 1);
	return (line);
}

static int	gnl_buffer(char **cache, int fd)
{
	char	*buffer;
	char	*temp;
	int		bytes_read;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (-1);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		if (*cache != NULL)
		{
			temp = *cache;
			*cache = ft_strjoin(*cache, buffer);
			free(temp);
		}
		else if (*cache == NULL)
			*cache = ft_strjoin(*cache, buffer);
	}
	free(buffer);
	return (bytes_read);
}

static int	gnl_find_end(char *cache)
{
	int	i;

	if (cache == NULL)
		return (0);
	i = 0;
	while (cache[i])
	{
		if (cache[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}