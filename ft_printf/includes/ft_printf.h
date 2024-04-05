/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 20:01:50 by aamirkha          #+#    #+#             */
/*   Updated: 2024/03/26 15:59:21 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <stdio.h>

typedef enum e_InputType
{
	InvalidInput = -1,
}	t_InputType;

int	ft_printf(char const *str, ...);
int	ft_parcer(char c, va_list arglist);
int	ft_putchar(char c);
int	ft_putstr(char *str);
int	ft_putnbr_signed(long long n, char const *base);
int	ft_input_handler(int const tmp, const char *const str);
int	ft_putnbr(unsigned int const nbr, char const *const base, size_t length);
int	ft_putptr(unsigned long long const nbr, char const *const base);

#endif // FT_PRINTF_H
