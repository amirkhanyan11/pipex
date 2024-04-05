/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 21:22:40 by aamirkha          #+#    #+#             */
/*   Updated: 2024/02/01 01:31:43 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	_to_char(int n)
{
	return (n + '0');
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == INT_MIN)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	if (n < 0)
	{
		n *= -1;
		ft_putchar_fd('-', fd);
	}
	if (n < 10)
	{
		ft_putchar_fd(_to_char(n), fd);
		return ;
	}
	ft_putnbr_fd((n / 10), fd);
	ft_putnbr_fd((n % 10), fd);
}
