/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:22:03 by aamirkha          #+#    #+#             */
/*   Updated: 2024/04/20 17:35:17 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


void childp(char *filename, int *_pipes, t_cmds *cmds, t_env _env)
{
	int _file = open_file(filename, READ);

	dup2(_file, STDIN_FILENO);
	dup2(_pipes[WRITE], STDOUT_FILENO);
	// close_pipes(_pipes);
	close(_pipes[0]);
	close(_pipes[1]);
	close(_file);
	execve(cmds->left[0], cmds->left, _env.env);
	pipex_free(cmds, _env.newenv);
	exit(EXIT_FAILURE);
}

void child2(char *filename, int *_pipes, t_cmds *cmds,  t_env _env)
{
	int _file = open_file(filename, WRITE);

	dup2(_file, STDOUT_FILENO);
	dup2(_pipes[READ], STDIN_FILENO);
	// close_pipes(_pipes);
	close(_pipes[0]);
	close(_pipes[1]);
	close(_file);
	execve(cmds->right[0], cmds->right, _env.env);
	pipex_free(cmds, _env.newenv);
	exit(EXIT_FAILURE);
}


void	pipex(char **av, char **env)
{
	int		_pipes[2];
	char	**newenv;
	t_cmds	cmds;
	int		pid;
	int		pid2;

	newenv = __slice(get_path(env));
	cmds = cmd_handle(av, newenv);
	if (-1 == pipe(_pipes))
		__terminate(errno);
	pid = fork();
	if (0 == pid)
	{
		// close_pipes(_pipes);
		// exit(EXIT_FAILURE);

		childp(av[1], _pipes, &cmds, __env_arg(env, newenv));
	}
	pid2 = fork();
	if (0 == pid2)
		child2(av[4], _pipes, &cmds, __env_arg(env, newenv));

	pipex_free(&cmds, newenv);
	close_pipes(_pipes);
	wait(NULL);
	wait(NULL);
}

// ./pipex file1 cmd1 cmd2 file2

int	main(int ac, char **av, char **env)
{
	if (ac != 5)
	{
		perror("Wrong arguments!\n");
		exit(EXIT_FAILURE);
	}
	pipex(av, env);
	return (1);
}
