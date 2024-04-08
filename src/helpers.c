/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 16:29:23 by aamirkha          #+#    #+#             */
/*   Updated: 2024/04/06 16:48:02 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void pipex_free(t_cmds cmds, int * fd, char **newenv)
{
	close(fd[0]);
	close(fd[1]);

	ft_free_split(cmds.left);
	ft_free_split(cmds.right);
	ft_free_split(newenv);
}

int open_file(char *name, int mode)
{
	int fd;
	if (0 == mode)
		fd = open(name, O_RDONLY);

	else
		fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0777);

	if (-1 == fd)
		mah();

	return fd;
}

void pipex_wait(int pid, int pid2)
{
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
}
