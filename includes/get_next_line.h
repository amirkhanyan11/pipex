/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:47:24 by aamirkha          #+#    #+#             */
/*   Updated: 2024/03/21 19:21:47 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <limits.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef enum e_sh
{
	__strchr,
	__strlen,
	__dealloc
}		t_sh;

char	*get_next_line(int fd);
char	*ft_frankenstein(char *str, char const c, t_sh mode);
void	ft_mutate(char **const memory, char const *const newline);
void	ft_append(char **const memory, char const *const buffer);
char	*ft_fetch(char **const memory);
void	ft_read(int const fd, char **const memory);

#endif // GET_NEXT_LINE_H
