/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_compare.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 08:55:37 by gacorrei          #+#    #+#             */
/*   Updated: 2023/05/25 08:55:58 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Returns length of largest string*/
int	len_compare(char *str1, char *str2)
{
	int	len1;
	int	len2;

	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	if (len1 >= len2)
		return (len1);
	else
		return (len2);
}
