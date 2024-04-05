/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 21:24:57 by aamirkha          #+#    #+#             */
/*   Updated: 2024/02/19 18:35:54 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int	ft_printf(char const *str, ...)
{
	int		plength;
	int		tmp;
	va_list	arglist;

	va_start(arglist, str);
	plength = 0;
	while (*str)
	{
		if (*str == '%')
		{
			tmp = ft_parcer(*(++str), arglist);
			if (!(*str))
				break ;
			plength += ft_input_handler(tmp, str);
		}
		else
			plength += ft_putchar(*(str));
		str++;
	}
	va_end(arglist);
	return (plength);
}
