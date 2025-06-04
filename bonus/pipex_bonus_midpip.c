/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_midpip.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilgar <yilgar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:29:23 by yilgar            #+#    #+#             */
/*   Updated: 2025/03/06 21:52:48 by yilgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	parent_modified(int *fd, char **av, char **ev)
{
	int	fileout;

	fileout = open(av[5], O_CREAT | O_WRONLY | O_TRUNC | O_APPEND, 0777);
	if (fileout == -1)
		ft_errorfd();
	dup2(fd[0], STDIN_FILENO);
	dup2(fileout, STDOUT_FILENO);
	close(fd[1]);
	execute(ev, av, 4);
}

static void	child_modified(int *fd, char **av, char **ev)
{
	int	filein;

	filein = open(av[1], O_RDONLY, 0777);
	if (filein == -1)
	{
		if (access(av[1], F_OK) != -1 && access(av[1], R_OK))
			ft_permden();
		ft_errorfd();
	}
	dup2(fd[1], STDOUT_FILENO);
	dup2(filein, STDIN_FILENO);
	close(fd[0]);
	execute(ev, av, 2);
}

void	with_pip(char **av, char **ev, int *fd)
{
	pid_t	pid1;

	pid1 = 0;
	if (pipe(fd) == -1)
		ft_error();
	pid1 = fork();
	if (pid1 == -1)
		ft_error();
	if (pid1 == 0)
		child_modified(fd, av, ev);
	waitpid(pid1, NULL, 0);
	parent_modified(fd, av, ev);
}
