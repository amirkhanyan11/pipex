/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 00:26:45 by kali              #+#    #+#             */
/*   Updated: 2024/01/25 17:21:12 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	_is_upper(int c)
{
	return ((c >= 'A' && c <= 'Z'));
}

static	int	_is_lower(int c)
{
	return ((c >= 'a' && c <= 'z'));
}

int	ft_isalpha(int c)
{
	return (_is_upper(c) || _is_lower(c));
}
