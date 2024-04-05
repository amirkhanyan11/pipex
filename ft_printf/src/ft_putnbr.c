/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 20:36:08 by aamirkha          #+#    #+#             */
/*   Updated: 2024/02/24 16:41:22 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int	ft_putnbr(unsigned int const nbr, char const *const base, size_t length)
{
	if (nbr < length)
		return (ft_putchar(base[nbr]));
	return (ft_putnbr(nbr / length, base, length) + ft_putnbr(nbr % length,
			base, length));
}

int	ft_putnbr_signed(long long n, char const *base)
{
	if (n < 0)
		return (ft_putchar('-') + ft_putnbr(-n, base, ft_strlen(base)));
	return (ft_putnbr(n, base, ft_strlen(base)));
}
