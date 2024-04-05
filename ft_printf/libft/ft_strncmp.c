/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 01:11:17 by kali              #+#    #+#             */
/*   Updated: 2024/01/25 16:21:20 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	if (!n)
		return (0);
	while (*str1 && *str2 && n > 1)
	{
		if (*str1 != *str2)
			break ;
		str1++;
		str2++;
		n--;
	}
	return ((const unsigned char)*str1 - (const unsigned char)*str2);
}
