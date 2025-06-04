/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilgar <yilgar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:11:10 by yilgar            #+#    #+#             */
/*   Updated: 2025/03/04 17:44:25 by yilgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

void	ft_permden(void)
{
	ft_putstr_fd("permission denied \n", 2);
	exit(126);
}

void	ft_args(void)
{
	ft_putstr_fd("invalid number of arguaments", 2);
	exit(2);
}

void	ft_error(void)
{
	ft_putstr_fd("command not found \n", 2);
	exit(127);
}

void	ft_errorfd(void)
{
	ft_putstr_fd("no such file or directory \n", 2);
	exit(1);
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
