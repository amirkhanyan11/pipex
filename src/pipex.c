/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:22:03 by aamirkha          #+#    #+#             */
/*   Updated: 2024/04/21 19:05:07 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


void childp(char *filename, int *_pipes, char *avcmd, t_env _env)
{
	int _file = open_file(filename, READ);

	char **cmd = cmd_handle(avcmd, _env.newenv);
	dup2(_file, STDIN_FILENO);
	dup2(_pipes[WRITE], STDOUT_FILENO);
	close_pipes(_pipes);
	close(_file);
	execve(cmd[0], cmd, _env.env);
	pipex_free(cmd, _env.newenv);
	exit(EXIT_FAILURE);
}

void child2(char *filename, int *_pipes, char *avcmd, t_env _env)
{
	int _file = open_file(filename, WRITE);
	char **cmd = cmd_handle(avcmd, _env.newenv);

	dup2(_file, STDOUT_FILENO);
	dup2(_pipes[READ], STDIN_FILENO);
	close_pipes(_pipes);
	close(_file);
	execve(cmd[0], cmd, _env.env);
	pipex_free(cmd, _env.newenv);
	exit(EXIT_FAILURE);
}

void	pipex(int ac, char **av, char **env)
{
	int		_pipes[2];
	char	**newenv;
	int		pid;

	newenv = __slice(get_path(env));
	if (-1 == pipe(_pipes))
		__terminate(errno);
	pid = fork();
	if (0 == pid)
		childp(av[1], _pipes, av[2], __env_arg(env, newenv));

	pid = fork();
	if (0 == pid)
		child2(av[ac - 1], _pipes, av[ac - 2], __env_arg(env, newenv));

	ft_free_split(newenv);
	close_pipes(_pipes);
}


// ./pipex file1 cmd1 cmd2 file2

int	main(int ac, char **av, char **env)
{
	if (ac < 5)
	{
		perror("pipex: ./pipex intfile cmd1 cmd2 outfile\n");
		exit(EXIT_FAILURE);
	}
	pipex(ac, av, env);
	while (-1 != wait(NULL))
		(void)ac;
	return (1);
}
