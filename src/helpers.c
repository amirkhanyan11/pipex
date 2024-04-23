/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 16:29:23 by aamirkha          #+#    #+#             */
/*   Updated: 2024/04/23 22:19:10 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex_free(char **cmd, char **newenv)
{
	ft_free_split(cmd);
	ft_free_split(newenv);
}

void	scroll(int fd)
{
	char	buf[BUFFER_SIZE];

	while (read(fd, buf, BUFFER_SIZE) > 0)
		(void)buf;
}

int	open_file(char *name, int mode)
{
	int	fd;

	if (READ == mode)
		fd = open(name, mode);
	else
		fd = open(name, mode, PERMISSIONS);
	if ((O_RDWR | O_CREAT) == mode)
		scroll(fd);
	if (-1 == fd)
		__terminate(strerror(errno));
	return (fd);
}

void	pipex_wait(int pid, int pid2, int *status)
{
	waitpid(pid, NULL, 0);
	waitpid(pid2, status, 0);
}

void	close_pipes(int *_pipes)
{
	close(_pipes[READ]);
	close(_pipes[WRITE]);
}
