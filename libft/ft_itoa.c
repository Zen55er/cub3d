/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 13:04:20 by gacorrei          #+#    #+#             */
/*   Updated: 2022/11/10 14:08:20 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_get_num(int n)
{
	unsigned int	nlt;

	if (n >= 0)
		nlt = n;
	else
		nlt = n * -1;
	return (nlt);
}

static int	ft_find_nlen(unsigned int nlt, int nl)
{
	while (nlt / 10 != 0)
	{
		nlt /= 10;
		nl++;
	}
	return (nl);
}

char	*ft_itoa(int n)
{
	char				*num;
	unsigned int		nlt;
	int					nl;

	nl = 1;
	if (n < 0)
		nl = 2;
	nlt = ft_get_num(n);
	nl = ft_find_nlen(nlt, nl);
	num = malloc(nl + 1);
	if (!num)
		return (NULL);
	nlt = ft_get_num(n);
	num[nl] = '\0';
	while (nl > 0)
	{
		num[nl - 1] = nlt % 10 + '0';
		nlt /= 10;
		nl--;
	}
	if (n < 0)
		num[0] = '-';
	return (num);
}
