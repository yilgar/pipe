/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilgar <yilgar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 21:50:21 by yilgar            #+#    #+#             */
/*   Updated: 2025/03/06 21:51:06 by yilgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	read_line(t_line **cache, int fd);
int		is_new_line(t_line *cache);
void	create_line(t_line *cache, char **line);
void	refactor_line(t_line **cache);

char	*get_next_lne(int fd)
{
	static t_line	*cache = NULL;
	char			*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_line(&cache, fd);
	if (!cache)
		return (NULL);
	create_line(cache, &line);
	refactor_line(&cache);
	return (line);
}

void	read_line(t_line **cache, int fd)
{
	char	*buffer;
	t_line	*new_node;
	int		output;

	while (!is_new_line(*cache))
	{
		buffer = ft_gnl_calloc(sizeof(*buffer), (BUFFER_SIZE + 1));
		output = read(fd, buffer, BUFFER_SIZE);
		if (output <= 0)
		{
			free(buffer);
			if (output == -1)
				ft_gnl_lstclear(cache, free);
			return ;
		}
		buffer[output] = '\0';
		new_node = ft_gnl_lstnew(buffer);
		if (!new_node || !buffer)
		{
			free(buffer);
			return ;
		}
		ft_gnl_lstadd_back(cache, new_node);
	}
}

int	is_new_line(t_line *cache)
{
	int		i;

	cache = ft_gnl_lstlast(cache);
	if (!cache)
		return (0);
	i = 0;
	while (cache->content[i] != '\0')
	{
		if (cache->content[i] == '\n')
		{
			cache->length = ++i;
			return (1);
		}
		i++;
	}
	cache->length = i;
	return (0);
}

void	create_line(t_line *cache, char **line)
{
	int		ln_size;
	int		i;
	t_line	*temp;

	temp = cache;
	ln_size = 0;
	while (temp)
	{
		ln_size += temp->length;
		temp = temp->next;
	}
	if (!ln_size)
		return ;
	*line = malloc(sizeof(**line) * (ln_size + 1));
	if (!line)
		return ;
	ln_size = 0;
	while (cache && cache->content)
	{
		i = 0;
		while (cache->content[i] && i < cache->length)
			(*line)[ln_size++] = cache->content[i++];
		cache = cache->next;
	}
	(*line)[ln_size] = '\0';
}

void	refactor_line(t_line **cache)
{
	t_line	*temp;
	t_line	*new_node;
	char	*content;
	int		i;
	int		size;

	size = 0;
	temp = ft_gnl_lstlast(*cache);
	if (!temp)
		return ;
	content = temp->content;
	size = temp->length;
	temp->content = NULL;
	ft_gnl_lstclear(cache, free);
	i = 0;
	if (content[size])
	{
		while (content[size])
			content[i++] = content[size++];
		content[i] = '\0';
		new_node = ft_gnl_lstnew(content);
		ft_gnl_lstadd_back(cache, new_node);
	}
	else
		free(content);
}
