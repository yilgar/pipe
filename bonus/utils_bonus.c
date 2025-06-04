/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilgar <yilgar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 20:59:41 by yilgar            #+#    #+#             */
/*   Updated: 2025/03/06 21:38:24 by yilgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	**line_take(char **str, char **test, char *line)
{
	int	i;

	i = 0;
	write(1, "pipex >", 7);
	line = get_next_lne(0);
	if (!line || !*line)
	{
		free_array(test);
		free(line);
		ft_args();
	}
	str = ft_split(line, ' ');
	while (str[i])
		i++;
	if (i < 2)
	{
		free_array(str);
		free(line);
		free(test);
		ft_args();
	}
	free(line);
	return (str);
}

static char	*linere(char **str, char **test, char *line)
{
	char	*tmp;
	int		j;

	j = 0;
	line = ft_strdup("");
	while (str[j + 1])
	{
		tmp = line;
		line = ft_strjoinex(tmp, ft_strtrim(str[j], "\" \n"));
		free(tmp);
		if (str[j + 2])
		{
			tmp = line;
			line = ft_strjoin(line, " ");
			free(tmp);
		}
		j++;
	}
	test[2] = line;
	test[3] = ft_strdup(str[j]);
	return (line);
}

char	**manipulated_pipe(char **av, int ac)
{
	char	**test;
	char	**str;
	char	*line;
	int		i;

	str = NULL;
	line = NULL;
	test = (char **)malloc(sizeof(void *) * (ac + 1));
	test[ac] = NULL;
	str = line_take(str, test, line);
	i = 0;
	while (i + 1 < ac - 1)
	{
		test[i] = ft_strdup(av[i + 1]);
		i++;
	}
	i = 0;
	line = linere(str, test, line);
	free_array(str);
	return (test);
}

void	main_helper(int ac, char **av, int *fileout)
{
	int	filein;

	filein = open(av[1], O_RDONLY);
	if (filein == -1)
		ft_errorfd();
	dup2(filein, STDIN_FILENO);
	close(filein);
	*fileout = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (*fileout == -1)
		ft_errorfd();
}

void	main_helper2(int ac, char **av, int *fd, int *fileout)
{
	if (ac < 6)
		ft_args();
	*fileout = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (*fileout == -1)
		ft_errorfd();
	handle_heredoc(av, fd);
}
