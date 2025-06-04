/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilgar <yilgar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:22:12 by yilgar            #+#    #+#             */
/*   Updated: 2025/03/06 22:04:59 by yilgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

void	child_exec(int *fd, char **av, char **ev)
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

void	parent_exec(int *fd, char **av, char **ev)
{
	int	fileout;

	fileout = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fileout == -1)
	{
		if (access(av[4], F_OK) != -1 && access(av[4], R_OK))
			ft_permden();
		ft_errorfd();
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(fileout, STDOUT_FILENO);
	close(fd[1]);
	execute(ev, av, 3);
}

void	without_pip(char **av, char **ev, int *fd)
{
	pid_t	pid1;

	pid1 = 0;
	if (pipe(fd) == -1)
		ft_error();
	pid1 = fork();
	if (pid1 == -1)
		ft_error();
	if (pid1 == 0)
		child_exec(fd, av, ev);
	waitpid(pid1, NULL, 0);
	parent_exec(fd, av, ev);
}

int	main(int ac, char **av, char **ev)
{
	int		fd[2];

	if (ac == 5)
		without_pip(av, ev, fd);
	else
		ft_args();
}
