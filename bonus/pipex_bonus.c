/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilgar <yilgar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 20:01:03 by yilgar            #+#    #+#             */
/*   Updated: 2025/03/06 21:02:50 by yilgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	execute_bonus(char **ev, char *av)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(av, ' ');
	if (!cmd || !*cmd)
	{
		free_array(cmd);
		ft_error();
	}
	path = pathfinder(ev, cmd[0]);
	if (!path)
	{
		free(path);
		free_array(cmd);
		ft_error();
	}
	if (execve(path, cmd, ev) == -1)
	{
		ft_error();
		free_array(cmd);
	}
}

void	exec_opbonus(char *av, char **ev, int *fd)
{
	pid_t	pid1;

	if (pipe(fd) == -1)
		ft_errorfd();
	pid1 = fork();
	if (pid1 == -1)
		ft_error();
	if (pid1 == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execute_bonus(ev, av);
		exit(1);
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	waitpid(pid1, NULL, 0);
}

void	handle_heredoc(char **av, int *fd)
{
	char	*line;

	if (pipe(fd) == -1)
		ft_errorfd();
	while (1)
	{
		write(1, "heredoc> ", 10);
		line = get_next_lne(0);
		if (!line)
			break ;
		if (!ft_strncmp(line, av[2], ft_strlen(av[2]))
			&& line[ft_strlen(av[2])] == '\n')
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		free(line);
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
}

static void	main_parse(int ac, int *fd, char **av, char **ev)
{
	if (ac == 4 && ft_strncmp(av[3], "|", 1) == 0)
		man_pipe(av, ev, fd, ac);
	else if (ac > 5 && ft_strncmp(av[3], "|", 1) == 0)
		with_pip(av, ev, fd);
}

int	main(int ac, char **av, char **ev)
{
	int	i;
	int	fd[2];
	int	fileout;

	fileout = 0;
	main_parse(ac, fd, av, ev);
	if (ac < 5)
		ft_args();
	if (!ft_strncmp(av[1], "here_doc", 9))
	{
		i = 3;
		main_helper2(ac, av, fd, &fileout);
	}
	else
	{
		i = 2;
		main_helper(ac, av, &fileout);
	}
	while (i < ac - 2)
		exec_opbonus(av[i++], ev, fd);
	dup2(fileout, STDOUT_FILENO);
	close(fileout);
	execute_bonus(ev, av[ac - 2]);
}
