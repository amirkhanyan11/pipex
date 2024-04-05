/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:14:29 by aamirkha          #+#    #+#             */
/*   Updated: 2024/01/26 15:22:26 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int	i;

	if (!dst && !src && len)
		return (dst);
	if (len && src < dst)
	{
		i = len - 1;
		while (i >= 0)
		{
			((char *const)dst)[i] = ((char *const)src)[i];
			i--;
		}
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
