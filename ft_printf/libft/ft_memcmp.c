/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 01:07:25 by kali              #+#    #+#             */
/*   Updated: 2024/01/27 17:22:56 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	if (!n)
		return (0);
	while (n > 1)
	{
		if (*((char const *)s1) != *((char const *)s2))
			break ;
		s1++;
		s2++;
		n--;
	}
	return (*(const unsigned char *)s1 - *(const unsigned char *)s2);
}
