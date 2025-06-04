/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilgar <yilgar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:22:19 by yilgar            #+#    #+#             */
/*   Updated: 2025/03/06 22:05:27 by yilgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include "../lib/libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

void	handle_pipe(char **tmp, char **ev, int *fd, pid_t pid1);
void	execute(char **ev, char **av, int index);
char	*pathfinder(char **ev, char *cmd);
char	*get_next_line(int fd);
char	*get_next_lne(int fd);
void	ft_args(void);
void	ft_error(void);
void	ft_errorfd(void);
void	ft_permden(void);
void	free_array(char **arr);
void	child_exec(int *fd, char **av, char **ev);
void	parent_exec(int *fd, char **av, char **ev);

#endif