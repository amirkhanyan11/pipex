/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 21:21:48 by aamirkha          #+#    #+#             */
/*   Updated: 2024/01/26 17:58:09 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	_count_words(char const *s, char const c);
static size_t	_current_len(char const **str, char const c);
static char		**_allocate(char const *str, char const c, size_t const SIZE);
static void		_skip_deallocate(char const **str, char const c, t_Mode mode);

char	**ft_split(char const *s, char c)
{
	if (!s)
		return (NULL);
	return (_allocate(s, c, _count_words(s, c)));
}

static	size_t	_count_words(char const *s, char const c)
{
	size_t	words;
	short	flag;

	words = 0;
	flag = 0;
	_skip_deallocate(&s, c, SKIP);
	while (*s)
	{
		if (*s != c)
			flag = 1;
		else if (*s == c && flag)
		{
			words++;
			flag = 0;
		}
		s++;
	}
	return (flag + words);
}

static	size_t	_current_len(char const **str, char const c)
{
	size_t	len;

	len = 0;
	while (**str && **str != c)
	{
		len++;
		(*str)++;
	}
	return (len);
}

static void	_skip_deallocate(char const **str, char const c, t_Mode mode)
{
	int	i;

	if (mode == DEALLOCATE)
	{
		i = c;
		while (i >= 0)
		{
			free((void *)str[i]);
			i--;
		}
		free(str);
	}
	else
		while (**str && **str == c)
			(*str)++;
}

static	char	**_allocate(char const *str, char const c, size_t const SIZE)
{
	char	**arr;
	char	*tmp;
	size_t	current_len;
	size_t	i;

	arr = (char **)malloc((SIZE + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	arr[SIZE] = NULL;
	i = 0;
	while (i < SIZE)
	{
		_skip_deallocate(&str, c, SKIP);
		tmp = (char *)str;
		current_len = _current_len(&str, c) + 1;
		arr[i] = (char *)malloc(current_len);
		if (!arr[i])
			_skip_deallocate((char const **)arr, i, DEALLOCATE);
		ft_strlcpy(arr[i], tmp, current_len);
		i++;
	}
	return (arr);
}
