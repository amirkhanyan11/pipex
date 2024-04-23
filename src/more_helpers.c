/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:19:57 by aamirkha          #+#    #+#             */
/*   Updated: 2024/04/23 16:49:27 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_append_pipex(char *left, char *right)
{
	char	*target;
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	target = (char *)malloc(ft_strlen(left) + ft_strlen(right) + 1);
	if (!target)
		return (NULL);
	while (left[i] || right[j])
	{
		if (left[i])
			target[k++] = left[i++];
		else
			target[k++] = right[j++];
	}
	target[k] = '\0';
	free(left);
	return (target);
}

char	*get_path(char **env)
{
	int		i;
	char	*t;

	i = 0;
	while (env[i])
	{
		t = ft_strnstr(env[i], "PATH=", ft_strlen(env[i]));
		if (NULL != t)
		{
			while (*t != '/')
				t++;
			return (ft_strdup(t));
		}
		i++;
	}
	return (NULL);
}

t_env	env_init(char **env)
{
	t_env	_env;

	_env.newenv = __slice(get_path(env));
	_env.env = env;
	return (_env);
}

void	wait_for_all(void)
{
	int	true;

	while (-1 != wait(NULL))
		true = (2 + 2 == 5);
}
