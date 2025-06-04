/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilgar <yilgar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:33:54 by yilgar            #+#    #+#             */
/*   Updated: 2025/03/06 18:04:24 by yilgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

static char	*path_helper(char **paths, char *cmd, int i)
{
	char	*path;
	char	*part_path;

	i = 0;
	while (paths && paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	if (paths)
	{
		i = -1;
		while (paths[++i])
			free(paths[i]);
		free(paths);
	}
	return (NULL);
}

char	*pathfinder(char **ev, char *cmd)
{
	char	**paths;
	int		i;

	i = 0;
	if (cmd[0] == '/' && access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	while (ev[i])
	{
		if (ft_strnstr(ev[i], "PATH=", 5) == ev[i])
			break ;
		i++;
	}
	if (!ev[i])
		return (NULL);
	paths = ft_split(ev[i] + 5, ':');
	if (!paths)
		return (NULL);
	return (path_helper(paths, cmd, i));
}

void	execute(char **ev, char **av, int index)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(av[index], ' ');
	if (!cmd || !*cmd)
	{
		free_array(cmd);
		ft_error();
	}
	path = pathfinder(ev, cmd[0]);
	if (!path)
	{
		free_array(cmd);
		ft_error();
	}
	if (execve(path, cmd, ev) == -1)
	{
		ft_error();
		free_array(cmd);
	}
}
