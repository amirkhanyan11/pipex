/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:22:03 by aamirkha          #+#    #+#             */
/*   Updated: 2024/04/22 15:28:24 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void _exec(char *avcmd,  t_env _env)
{
	char **cmd = cmd_handle(avcmd, _env.newenv);
	execve(cmd[0], cmd, _env.env);
	pipex_free(cmd, _env.newenv);
	exit(EXIT_FAILURE);
}

void pipinthisbitch(char *avcmd, t_env _env, int mode)
{
	int _pipe[2];

	if (-1 == pipe(_pipe))
		__terminate(errno);

	int pid = fork();
	if (-1 == pid)
		__terminate(errno);
	if (0 == pid)
	{
		close(_pipe[READ]);
		if (LAST != mode)
			dup2(_pipe[WRITE], STDOUT_FILENO);
		_exec(avcmd, _env);
	}
	close(_pipe[WRITE]);
	dup2(_pipe[READ], STDIN_FILENO); // yeeeah wireeee
}

void	pipex(int ac, char **av, char **env)
{
	char	**newenv;

	newenv = __slice(get_path(env));
	t_env _env = __env_arg(env, newenv);

	int infile = open_file(av[1], READ);
	int outfile = open_file(av[ac - 1], WRITE);

	dup2(infile, STDIN_FILENO);

	int i = 2;
	while (i < ac - 1)
	{
		int mode = (ac - 2 == i);
		if (LAST == mode)
			dup2(outfile, STDOUT_FILENO);
		pipinthisbitch(av[i++], _env, mode);
	}


	close(infile);
	close(outfile);
	ft_free_split(newenv);

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
	// execve(av[1], NULL, NULL	);
	return (1);
}
