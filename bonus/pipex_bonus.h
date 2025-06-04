/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilgar <yilgar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:33:30 by yilgar            #+#    #+#             */
/*   Updated: 2025/03/06 22:04:22 by yilgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../header/pipex.h"

void	execute_bonus(char **ev, char *av);
char	*pathfinder(char **ev, char *cmd);
void	with_pip(char **av, char **ev, int *fd);
void	man_pipe(char **av, char **ev, int *fd, int ac);
void	main_helper(int ac, char **av, int *fileout);
void	main_helper2(int ac, char **av, int *fd, int *fileout);
char	**manipulated_pipe(char **av, int ac);
char	*ft_strjoinex(char const *s1, char *s2);
void	handle_heredoc(char **av, int *fd);

#endif