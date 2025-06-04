/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilgar <yilgar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 21:50:16 by yilgar            #+#    #+#             */
/*   Updated: 2025/03/06 21:51:48 by yilgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "../../header/pipex.h"
# include <stdlib.h>
# include <unistd.h>

typedef struct s_line
{
	char			*content;
	int				length;
	struct s_line	*next;
}					t_line;

char	*get_next_lne(int fd);

t_line	*ft_gnl_lstnew(char *content);

t_line	*ft_gnl_lstlast(t_line *lst);

void	ft_gnl_lstadd_back(t_line **lst, t_line *new);

void	ft_gnl_lstclear(t_line **lst, void (*del)(void *));

void	*ft_gnl_calloc(size_t nmemb, size_t size);
#endif