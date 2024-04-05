/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 20:03:00 by aamirkha          #+#    #+#             */
/*   Updated: 2024/01/27 01:27:23 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*_join(char const *s1, char const *s2);

char	*ft_strjoin(char const *s1, char const *s2)
{
	if (!s1 || !s2)
		return (NULL);
	return (_join(s1, s2));
}

static	char	*_join(char const *s1, char const *s2)
{
	char	*join;
	size_t	lenjoin;

	lenjoin = ft_strlen(s1) + ft_strlen(s2) + 1;
	join = (char *)malloc(lenjoin);
	if (join)
	{
		(void)ft_strlcpy(join, s1, lenjoin);
		(void)ft_strlcat(join, s2, lenjoin);
	}
	return (join);
}
