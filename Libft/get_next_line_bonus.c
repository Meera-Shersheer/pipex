/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 19:28:58 by mshershe          #+#    #+#             */
/*   Updated: 2025/02/14 19:14:32 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	*ft_free(char **data)
{
	if (!data)
		return (NULL);
	if (*data)
	{
		free(*data);
		*data = NULL;
	}
	return (NULL);
}

static char	*gnl_get_line(char **line)
{
	int		i;
	char	*buff;
	char	*res;

	if (line == NULL || *line == NULL)
		return (NULL);
	i = gnl_strchr(*line, '\n');
	if (i == -1)
	{
		if (gnl_strlen(*line) == 0)
			return (ft_free(line));
		res = gnl_strdup(*line);
		ft_free(line);
		if (!res)
			return (NULL);
		return (res);
	}
	buff = *line;
	res = gnl_substr(*line, 0, i + 1);
	if (res == NULL)
		ft_free (line);
	*line = gnl_substr(*line, i + 1, gnl_strlen(*line) - i - 1);
	free(buff);
	return (res);
}

char	*comp(char **buffer, int fd, char **line, int *read_bytes)
{
	*buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (*buffer == NULL)
		return (ft_free(line));
	*read_bytes = read(fd, *buffer, BUFFER_SIZE);
	if ((*read_bytes) == -1)
	{
		free(*buffer);
		return (ft_free(line));
	}
	else if ((*read_bytes) != 0)
	{
		(*buffer)[(*read_bytes)] = '\0';
		(*line) = gnl_strjoin(*line, *buffer);
	}
	ft_free(buffer);
	return (*line);
}

char	*get_next_line(int fd)
{
	static char	*line[OPEN_MAX];
	int			read_bytes;
	char		*buffer;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	read_bytes = 1;
	if (line[fd] == NULL)
	{
		line[fd] = gnl_strdup("");
		if (line[fd] == NULL)
			return (NULL);
	}
	while (read_bytes > 0)
	{
		if (gnl_strchr(line[fd], '\n') == -1)
		{
			comp(&buffer, fd, &(line[fd]), &read_bytes);
			if (!(line[fd]))
				return (ft_free(&line[fd]));
		}
		else
			return (gnl_get_line(&line[fd]));
	}
	return (gnl_get_line(&line[fd]));
}
