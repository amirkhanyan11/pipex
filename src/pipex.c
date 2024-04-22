/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:22:03 by aamirkha          #+#    #+#             */
/*   Updated: 2024/04/22 20:36:40 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void _exec(char *avcmd,  t_env _env)
{
	char **cmd = cmd_handle(avcmd, _env.newenv);
	// ft_putstr_fd(avcmd, 2);
	// ft_putstr_fd("\n", 2);
	execve(cmd[0], cmd, _env.env);
	pipex_free(cmd, _env.newenv);
	exit(EXIT_FAILURE);
}

void pipinthisbitch(char *avcmd, t_env _env, int mode)
{
	int _pipe[2];

	if (-1 == pipe(_pipe))
		__terminate(strerror(errno));

	int pid = fork();
	if (-1 == pid)
		__terminate(strerror(errno));
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

void	here_doc_put_in(char **av, int *_pipe)
{
	char	*line;

	close(_pipe[READ]);
	while (1)
	{
		line = get_next_line(0);
		if (!ft_strncmp(line, av[2], ft_strlen(av[2])))
		{
			free(line);
			exit(0);
		}
		ft_putstr_fd(line, _pipe[WRITE]);
		free(line);
	}
}

void	here_doc(char **av)
{
	int		_pipe[2];
	pid_t	pid;

	if (pipe(_pipe) == -1)
		exit(0);
	pid = fork();
	if (pid == -1)
		__terminate(strerror(errno));
	if (!pid)
		here_doc_put_in(av, _pipe);
	else
	{
		close(_pipe[WRITE]);
		dup2(_pipe[READ], STDIN_FILENO);
		wait(NULL);
	}
}

void	pipex(int ac, char **av, char **env)
{
	char	**newenv;
	int infile;
	int outfile;
	int i;

	newenv = __slice(get_path(env));
	t_env _env = __env_arg(env, newenv);
	outfile = open_file(av[ac - 1], WRITE);

	if (!ft_strncmp(av[1], "here_doc", ft_strlen(av[1])))
	{
		i = 3;
		here_doc(av);
	}
	else
	{
		i = 2;
		infile = open_file(av[1], READ);
		dup2(infile, STDIN_FILENO);
	}

	while (i < ac - 1)
	{
		int mode = (i == ac - 2);
		if (LAST == mode)
			dup2(outfile, STDOUT_FILENO);

		pipinthisbitch(av[i++], _env, mode);
	}

	if (!ft_strncmp(av[1], "here_doc", ft_strlen(av[1])))
		close(infile);

	close(outfile);
	ft_free_split(newenv);

}


// ./pipex file1 cmd1 cmd2 file2

int	main(int ac, char **av, char **env)
{
	if (ac < 5)
	{
		perror("pipex: ./pipex infile cmd1 cmd2 outfile\n");
		exit(EXIT_FAILURE);
	}

	pipex(ac, av, env);
	while (-1 != wait(NULL))
		(void)ac;

	return (1);
}
