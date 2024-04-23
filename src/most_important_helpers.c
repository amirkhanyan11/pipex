/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   most_important_helpers.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:40:42 by aamirkha          #+#    #+#             */
/*   Updated: 2024/04/23 16:49:39 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	_exec(char *avcmd, t_env _env)
{
	char	**cmd;

	cmd = cmd_handle(avcmd, _env.newenv);
	execve(cmd[0], cmd, _env.env);
	pipex_free(cmd, _env.newenv);
	exit(EXIT_FAILURE);
}

void	makepipe(char *avcmd, t_env _env, int mode)
{
	int	_pipe[2];
	int	pid;

	if (-1 == pipe(_pipe))
		__terminate(strerror(errno));
	pid = fork();
	if (-1 == pid)
		__terminate(strerror(errno));
	if (0 == pid)
	{
		close(_pipe[READ]);
		if (LAST != mode)
			dup2(_pipe[WRITE], STDOUT_FILENO);
		_exec(avcmd, _env);
	}
	dup2(_pipe[READ], STDIN_FILENO);
	close_pipes(_pipe);
}

void	here_doc_get(char **av, int *_pipe)
{
	char	*line;

	close(_pipe[READ]);
	line = get_next_line(STDIN_FILENO);
	while (ft_strncmp(line, av[LIMITER], ft_strlen(av[LIMITER])))
	{
		ft_putstr_fd(line, _pipe[WRITE]);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	exit(EXIT_SUCCESS);
}

void	here_doc(char **av)
{
	int		_pipe[2];
	pid_t	pid;

	if (pipe(_pipe) == -1)
		__terminate(strerror(errno));
	pid = fork();
	if (pid == -1)
		__terminate(strerror(errno));
	if (!pid)
		here_doc_get(av, _pipe);
	else
	{
		close(_pipe[WRITE]);
		dup2(_pipe[READ], STDIN_FILENO);
		wait(NULL);
	}
}

void	makepipe_wrapper(int ac, char **av, int *_files, t_env _env)
{
	int	i;
	int	mode;

	i = 2 + (!ft_strncmp(av[1], "here_doc", ft_strlen(av[1])));
	while (i < ac - 1)
	{
		mode = (i == ac - 2);
		if (LAST == mode)
			dup2(_files[WRITE], STDOUT_FILENO);
		makepipe(av[i++], _env, mode);
	}
}
