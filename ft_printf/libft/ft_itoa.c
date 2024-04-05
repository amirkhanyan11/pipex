/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 18:08:03 by kali              #+#    #+#             */
/*   Updated: 2024/01/27 01:19:59 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	_digit_count(int const n);
static int		_calculate_size(int const n);
static char		_to_char(int n);
static char		*_allocate(int n);

char	*ft_itoa(int n)
{
	return (_allocate(n));
}

static	size_t	_digit_count(int const n)
{
	if (n == 0)
		return (0);
	return (1 + _digit_count(n / 10));
}

static int	_calculate_size(int const n)
{
	if (n <= 0)
		return (_digit_count(n) + 1);
	return (_digit_count(n));
}

static char	_to_char(int n)
{
	if (n < 0)
		n *= -1;
	return (n + '0');
}

static	char	*_allocate(int n)
{
	char	*dst;
	int		size;
	int		sign;

	sign = (n < 0);
	size = _calculate_size(n);
	dst = (char *)malloc(size + 1);
	if (!dst)
		return (NULL);
	dst[size] = '\0';
	while (size > 0)
	{
		dst[size - 1] = _to_char(n % 10);
		n /= 10;
		size--;
	}
	if (sign)
		dst[0] = '-';
	return (dst);
}
