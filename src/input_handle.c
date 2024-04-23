/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:22:35 by aamirkha          #+#    #+#             */
/*   Updated: 2024/04/23 21:46:46 by aamirkha         ###   ########.fr       */
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

char	**addbash(char **prev, char **newenv)
{
	int		i;
	char	**newcmd;
	int		j;

	i = 0;
	while (prev[i])
	{
		i++;
	}
	newcmd = malloc(sizeof(char *) * (i + 2));
	if (NULL == newcmd)
		__terminate("pipex: bad alloc\n");
	newcmd[0] = cmd_lookup("bash", newenv);
	if (NULL == newcmd[0])
		__terminate("pipex: bash not found\n");
	j = 0;
	while (prev[j])
	{
		newcmd[j + 1] = prev[j];
		j++;
	}
	newcmd[j + 1] = prev[j];
	return (newcmd);
}

char	**cmd_handle(char *avcmd, char **newenv)
{
	char	**cmd;
	char	*c;

	cmd = ft_split(avcmd, ' ');
	c = cmd_lookup(cmd[0], newenv);
	if (NULL != c)
	{
		free(cmd[0]);
		cmd[0] = c;
	}
	else if (is_script(avcmd) && 0 == access(avcmd, F_OK))
	{
		return (addbash(cmd, newenv));
	}
	else
		__terminate("pipex: command not found\n");
	return (cmd);
}
