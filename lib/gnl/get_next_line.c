/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilgar <yilgar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 21:50:11 by yilgar            #+#    #+#             */
/*   Updated: 2025/03/06 21:50:40 by yilgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/pipex.h"

char	*ft_strjoin1(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*new;

	i = ft_strlen(s1) + ft_strlen(s2);
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	new = (char *)malloc(sizeof(char) * (i + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	while (s2[j])
		new[i++] = s2[j++];
	new[i] = '\0';
	free(s1);
	return (new);
}

static char	*sub_line(char *buffer)
{
	int		i;
	char	*line;

	i = 0;
	if (!buffer || !*buffer)
		return (NULL);
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		line = (char *)malloc(sizeof(char) * (i + 2));
	else
		line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*checkpoint(char *buffer)
{
	int		i;
	char	*cpoint;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	cpoint = ft_strdup(&buffer[i + 1]);
	if (!cpoint)
	{
		free(cpoint);
		return (NULL);
	}
	free(buffer);
	return (cpoint);
}

static char	*readbuffer(int fd, char *buffer)
{
	char	*temp;
	int		bytes_read;

	temp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp)
		return (NULL);
	if (!buffer)
		buffer = ft_strdup("");
	bytes_read = read(fd, temp, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		temp[bytes_read] = '\0';
		buffer = ft_strjoin1(buffer, temp);
		if (ft_strchr(buffer, '\n'))
			break ;
		bytes_read = read(fd, temp, BUFFER_SIZE);
	}
	free(temp);
	if (bytes_read < 0)
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = readbuffer(fd, buffer);
	if (!buffer)
		return (NULL);
	line = sub_line(buffer);
	buffer = checkpoint(buffer);
	return (line);
}
