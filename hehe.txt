

#include "pipex.h"

// ./pipex file1 cmd1 cmd2 file2

void child(char **cmd, char **newenv, int *fd, int i_o, int fileno, int x)
{

	dup2(fd[i_o], fileno);
	dup2(fileno, i_o);
	close(fd[0]);
	close(fd[1]);
	close(fileno);
	close(x);
	execve(cmd[0], cmd, newenv);
}

void pipex_free(t_cmds cmds, char **newenv)
{
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
		fd = open(name, O_WRONLY);

	if (-1 == fd)
	{
		printf("failed to open %s\n", name);
		mah();
	}

	return fd;
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
	printf("yep");
	int fd[2];

	char **newenv = __slice(get_path(env));
	t_cmds cmds = cmd_handle(av, newenv);

	int fd1 = open_file(av[1], 0);
	int fd2 = open_file(av[4], 1);

	if (-1 == pipe(fd))
		mah();

	int pid = fork();

	if (0 == pid) // child 1
		child(cmds.left, newenv, fd, 1, fd1, fd2); // terminates the child process

	int pid2 = fork();

	if (0 == pid2) // child 2
		child(cmds.right, newenv, fd, 0, fd2, fd1); // terminates the child process

	close(fd1);
	close(fd2);
	pipex_wait(fd, pid, pid2);
	pipex_free(cmds, newenv);
}

int main(int ac, char **av, char **env)
{
	// cmd_handle("aaa", env);
	pipex(ac, av, env);

	return 0;
}
