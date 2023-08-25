/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 10:24:57 by gacorrei          #+#    #+#             */
/*   Updated: 2022/11/11 11:29:43 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*ns1;
	unsigned char	*ns2;

	i = 0;
	ns1 = (unsigned char *) s1;
	ns2 = (unsigned char *) s2;
	while (i < n)
	{
		if (ns1[i] != ns2[i])
		{
			return (ns1[i] - ns2[i]);
		}
		i++;
	}
	return (0);
}
