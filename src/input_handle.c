/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:22:35 by aamirkha          #+#    #+#             */
/*   Updated: 2024/04/22 15:28:07 by aamirkha         ###   ########.fr       */
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
	path = ft_append_pipex(path, "/");
	path = ft_append_pipex(path, cmd);
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

char	**cmd_handle(char *avcmd,  char **newenv)
{

	char **cmd = ft_split(avcmd, ' ');
	char *c = cmd_lookup(cmd[0], newenv);


	if (NULL != c)
	{
		free(cmd[0]);
		cmd[0] = c;
	}
	else if (0 == access(avcmd, F_OK | X_OK))
	{
		free(cmd[0]);
		char *t = ft_strdup("./");
		cmd[0] = ft_append_pipex(t, avcmd);
		ft_putstr_fd(cmd[0], 2);
	}

	else
		perror("pipex: command not found\n");

	return (cmd);
}
