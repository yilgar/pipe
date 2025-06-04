/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_lastpip.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilgar <yilgar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 06:00:07 by yilgar            #+#    #+#             */
/*   Updated: 2025/03/06 21:52:20 by yilgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	execute_ex(char **ev, char **av, int index)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(av[index], ' ');
	if (!cmd || !*cmd)
	{
		free_array(av);
		free_array(cmd);
		ft_error();
	}
	path = pathfinder(ev, cmd[0]);
	if (!path)
	{
		free_array(av);
		free_array(cmd);
		ft_error();
	}
	if (execve(path, cmd, ev) == -1)
	{
		free_array(av);
		free_array(cmd);
		ft_error();
	}
}

static void	child_manpipe(int *fd, char **av, char **ev)
{
	int	filein;

	filein = open(av[0], O_RDONLY, 0777);
	if (filein == -1)
	{
		if (access(av[0], F_OK) != -1 && access(av[0], R_OK))
		{
			free_array(av);
			ft_permden();
		}
		free_array(av);
		ft_errorfd();
	}
	dup2(fd[1], STDOUT_FILENO);
	dup2(filein, STDIN_FILENO);
	close(fd[0]);
	execute_ex(ev, av, 1);
}

static void	parent_manpipe(int *fd, char **av, char **ev)
{
	int	fileout;

	fileout = open(av[3], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fileout == -1)
	{
		free_array(av);
		if (access(av[3], F_OK) != -1 && access(av[3], R_OK))
		{
			free_array(av);
			ft_permden();
		}
		free_array(av);
		ft_errorfd();
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(fileout, STDOUT_FILENO);
	close(fd[1]);
	execute_ex(ev, av, 2);
}

void	man_pipe(char **av, char **ev, int *fd, int ac)
{
	char	**cmd;
	pid_t	pid1;

	pid1 = 0;
	cmd = manipulated_pipe(av, ac);
	if (!cmd)
		free_array(cmd);
	if (pipe(fd) == -1)
		ft_error();
	pid1 = fork();
	if (pid1 == -1)
		ft_error();
	if (pid1 == 0)
		child_manpipe(fd, cmd, ev);
	waitpid(pid1, NULL, 0);
	parent_manpipe(fd, cmd, ev);
}
