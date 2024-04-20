/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:22:35 by aamirkha          #+#    #+#             */
/*   Updated: 2024/04/20 17:22:10 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**__slice(char *path)
{
	char	**arr;

	arr = ft_split(path, ':');
	free(path);
	return (arr);
}

void	__terminate(int err)
{
	perror(strerror(err));
	exit(EXIT_FAILURE);
}

char	*current_lookup(char *cmd, char *path)
{
	path = ft_strdup(path);
	path = ft_append(path, "/");
	path = ft_append(path, cmd);
	if (0 == access(path, F_OK))
		return (path);
	free(path);
	return (NULL);
}

char	*cmd_lookup(char *cmd, char **newenv)
{
	int		i;
	char	*current;

	i = 0;
	current = NULL;
	while (newenv[i])
	{
		current = current_lookup(cmd, newenv[i]);
		if (0 != current)
			break ;
		i++;
	}
	return (current);
}

t_cmds	cmd_handle(char **av, char **newenv)
{
	t_cmds	res;
	char	*c1;
	char	*c2;

	res.left = ft_split(av[2], ' ');
	res.right = ft_split(av[3], ' ');
	c1 = cmd_lookup(res.left[0], newenv);
	c2 = cmd_lookup(res.right[0], newenv);
	if (!c1 || !c2)
		perror("pipex: command not found\n");
	if (c1)
	{
		free(res.left[0]);
		res.left[0] = c1;
	}
	if (c2)
	{
		free(res.right[0]);
		res.right[0] = c2;
	}
	return (res);
}
