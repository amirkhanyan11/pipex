/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parcer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 20:36:08 by aamirkha          #+#    #+#             */
/*   Updated: 2024/02/24 16:41:22 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int	ft_parcer(char c, va_list arglist)
{
	char const	*hex_lower;
	char const	*hex_upper;
	char const	*decimal;

	hex_lower = "0123456789abcdef";
	hex_upper = "0123456789ABCDEF";
	decimal = "0123456789";
	if (c == 'd' || c == 'i')
		return (ft_putnbr_signed(va_arg(arglist, int), decimal));
	else if (c == 'c')
		return (ft_putchar(va_arg(arglist, int)));
	else if (c == 's')
		return (ft_putstr(va_arg(arglist, char *)));
	else if (c == 'x')
		return (ft_putnbr(va_arg(arglist, int), hex_lower,
				ft_strlen(hex_lower)));
	else if (c == 'X')
		return (ft_putnbr(va_arg(arglist, int), hex_upper,
				ft_strlen(hex_upper)));
	else if (c == 'u')
		return (ft_putnbr(va_arg(arglist, int), decimal, ft_strlen(decimal)));
	else if (c == 'p')
		return ((ft_putstr("0x") + ft_putptr(va_arg(arglist, long long),
					"0123456789abcdef")));
	return (InvalidInput);
}
