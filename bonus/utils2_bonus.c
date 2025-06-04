/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilgar <yilgar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 21:09:19 by yilgar            #+#    #+#             */
/*   Updated: 2025/03/06 21:11:48 by yilgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*ft_strjoinex(char const *s1, char *s2)
{
	char	*s;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1) + ft_strlen(s2);
	s = (char *)malloc(i + 1);
	if (!s)
		return (0);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		s[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		s[i] = s2[j];
		i++;
		j++;
	}
	s[i] = '\0';
	return (free(s2), s);
}
