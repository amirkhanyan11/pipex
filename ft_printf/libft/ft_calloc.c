/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:39:07 by aamirkha          #+#    #+#             */
/*   Updated: 2024/01/29 20:32:24 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	_sign_check(long long lcount, long long lsize)
{
	return ((lcount < 0 && lsize != 0) || (lcount != 0 && lsize < 0));
}

static	int	_max_check(long long lcount, long long lsize)
{
	return (lsize >= INT_MAX || lcount >= INT_MAX);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*rtn;

	if (_sign_check(count, size) || _max_check(count, size))
		return (NULL);
	rtn = malloc(size * count);
	if (rtn)
		ft_bzero(rtn, (size * count));
	return (rtn);
}
