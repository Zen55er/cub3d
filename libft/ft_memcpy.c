/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 10:27:41 by gacorrei          #+#    #+#             */
/*   Updated: 2022/11/09 11:58:51 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*new_d;
	char		*new_s;

	if (!dest && !src)
		return (NULL);
	i = 0;
	new_d = (char *) dest;
	new_s = (char *) src;
	while (i < n)
	{
		new_d[i] = new_s[i];
		i++;
	}
	return (dest);
}
