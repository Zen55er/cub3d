/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 14:07:09 by gacorrei          #+#    #+#             */
/*   Updated: 2022/11/09 12:11:21 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		l1;
	int		l2;
	int		tl;
	char	*new;

	if (!s1 || !s2)
		return (0);
	i = 0;
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	tl = l1 + l2 + 1;
	new = malloc(tl);
	if (!new)
		return (NULL);
	while (i < tl)
	{
		if (i < l1)
			new[i] = s1[i];
		else
			new[i] = s2[i - l1];
		i++;
	}
	return (new);
}
