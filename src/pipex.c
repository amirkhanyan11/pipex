

#include "pipex.h"

// ./pipex file1 cmd1 cmd2 file2

void child(char **cmd, char **newenv, int *fd, int fileno)
{
	dup2(fd[fileno], fileno);
	close(fd[0]);
	close(fd[1]);

	execve(cmd[0], cmd, newenv);
}

void pipex_free(char *c1, char *c2, char **newenv)
{
	free(c1);
	free(c2);
	ft_free_split(newenv);
}

void pipex_wait(int *fd, int pid, int pid2)
{
	close(fd[0]);
	close(fd[1]);

	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
}

void pipex(int ac, char **av, char **env)
{
	int fd[2];

	char **newenv = __slice(get_path(env));

	char *c1 = cmd_lookup(av[2], newenv);
	char *c2 = cmd_lookup(av[3], newenv);


	if (!c1 || !c2)
		mah();

	char *cmd[] = {c1, av[1], NULL};
	char *cmd2[] = {c2, av[4], NULL};

	if (-1 == pipe(fd))
		mah();

	int pid = fork();

	if (0 == pid) // child 1
		child(cmd, newenv, fd, 1); // terminates the child process

	int pid2 = fork();

	if (0 == pid2) // child 2
		child(cmd2, newenv, fd, 0); // terminates the child process

	pipex_wait(fd, pid, pid2);
	pipex_free(c1, c2, newenv);
}

int main(int ac, char **av, char **env)
{
	// cmd_handle("aaa", env);
	pipex(ac, av, env);

	return 0;
}
