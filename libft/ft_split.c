/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 11:40:49 by gacorrei          #+#    #+#             */
/*   Updated: 2022/11/09 14:28:25 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_free(int x, char **split)
{
	while (x-- > 0)
		free (split[x]);
	free (split);
	return ;
}

static void	ft_write(char **split, char *s, char c, int size)
{
	int		i;
	int		x;

	i = 0;
	x = -1;
	while (++x < size)
	{
		while (*s == c)
			s++;
		while (s[i] != c && s[i])
			i++;
		if ((s[i] == c || s[i] == '\0') && s[i - 1] != c)
		{
			split[x] = ft_substr(s, 0, i);
			if (!split[x])
			{
				ft_free(x, split);
				return ;
			}
			s = &s[i];
			i = 0;
		}
	}
	split[x] = 0;
	return ;
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		i;
	int		j;

	if (!s)
		return (0);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			j++;
		i++;
	}
	split = (char **)malloc (sizeof(char *) * (j + 1));
	if (!split)
		return (0);
	ft_write(split, (char *) s, c, j);
	return (split);
}
