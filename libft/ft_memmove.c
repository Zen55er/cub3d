/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 10:24:20 by gacorrei          #+#    #+#             */
/*   Updated: 2022/11/09 11:59:43 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*ndest;
	unsigned char	*nsrc;

	i = 0;
	ndest = (unsigned char *) dest;
	nsrc = (unsigned char *) src;
	while (ndest < nsrc && i < n)
	{
		ndest[i] = nsrc[i];
		i++;
	}
	while (ndest > nsrc && n > 0)
	{
		ndest[n - 1] = nsrc[n - 1];
		n--;
	}
	return (dest);
}
