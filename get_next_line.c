/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsahin <elsahin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 11:02:55 by elsahin           #+#    #+#             */
/*   Updated: 2025/11/17 12:42:28 by elsahin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_loop(int fd, char *rest, char *buffer)
{
	int	bytes;

	bytes = 1;
	while (!ft_strchr(rest, '\n') && bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(rest);
			return (NULL);
		}
		buffer[bytes] = '\0';
		rest = ft_strjoin(rest, buffer);
		if (!rest)
			return (NULL);
	}
	return (rest);
}

char	*read_and_join(int fd, char *rest)
{
	char	*buffer;
	char	*result;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	result = read_loop(fd, rest, buffer);
	free(buffer);
	return (result);
}

char	*extract_line(char *rest)
{
	char	*line;
	int		i;

	if (!rest || rest[0] == '\0')
		return (NULL);
	i = 0;
	while (rest[i] && rest[i] != '\n')
		i++;
	if (rest[i] == '\n')
		i++;
	line = ft_substr(rest, 0, i);
	return (line);
}

char	*clean_rest(char *rest)
{
	char	*new_rest;
	int		i;

	i = 0;
	while (rest[i] && rest[i] != '\n')
		i++;
	if (!rest[i])
	{
		free(rest);
		return (NULL);
	}
	i++;
	new_rest = ft_substr(rest, i, ft_strlen(rest) - i);
	free(rest);
	if (!new_rest)
		return (NULL);
	if (new_rest[0] == '\0')
	{
		free(new_rest);
		return (NULL);
	}
	return (new_rest);
}

char	*get_next_line(int fd)
{
	static char	*rest = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	rest = read_and_join(fd, rest);
	if (!rest)
		return (NULL);
	line = extract_line(rest);
	rest = clean_rest(rest);
	return (line);
}
