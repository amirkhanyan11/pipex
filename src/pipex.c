

#include "pipex.h"

void pipex(int ac, char **av, char **env)
{
	int fd[2];

	char **newenv = __slice(get_path(env));
	t_cmds cmds = cmd_handle(av, newenv);

	int first = open_file(av[1], 0);
	int second = open_file(av[4], 1);

	if (-1 == pipe(fd))
		mah();

	int pid = fork();

	if (0 == pid) // child 1
	{
		dup2(first, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);

		close(fd[0]);
		close(fd[1]);

		close(first);
		close(second);

		execve(cmds.left[0], cmds.left, newenv);
	}

	int pid2 = fork();

	if (0 == pid2) // child 2
	{
		dup2(second, STDOUT_FILENO);
		dup2(fd[0], STDIN_FILENO);

		close(fd[0]);
		close(fd[1]);

		close(first);
		close(second);

		execve(cmds.right[0], cmds.right, newenv);
	}

	pipex_free(cmds, fd, newenv);
	pipex_wait(pid, pid2);
}

int main(int ac, char **av, char **env)
{
	// cmd_handle("aaa", env);
	pipex(ac, av, env);

	return 0;
}
