

#include "pipex.h"


void handle_files(int ffile, int sfile)
{
	if (ffile != 0)
		close(ffile);
	if (sfile != 1)
		close(sfile);
}

void pipex(int ac, char **av, char **env, int ffile, int sfile)
{
	int fd[2];

	char **newenv = __slice(get_path(env));
	t_cmds cmds = cmd_handle(av, newenv);

	if (ffile != STDIN_FILENO)
		ffile = open_file(av[1], 0);

	if (sfile != STDOUT_FILENO)
		sfile = open_file(av[4], 1);

	if (-1 == pipe(fd))
		mah();

	int pid = fork();

	if (0 == pid) // child 1
	{
		dup2(ffile, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);

		close(fd[0]);
		close(fd[1]);

		handle_files(ffile, sfile);

		if (-1 == execve(cmds.left[0], cmds.left, newenv))
			mah();
	}

	int pid2 = fork();

	if (0 == pid2) // child 2
	{
		dup2(sfile, STDOUT_FILENO);
		dup2(fd[0], STDIN_FILENO);

		close(fd[0]);
		close(fd[1]);

		handle_files(ffile, sfile);

		if (-1 == execve(cmds.right[0], cmds.right, newenv))
			mah();
	}

	handle_files(ffile, sfile);
	pipex_free(cmds, fd, newenv);
	pipex_wait(pid, pid2);
}

// ./pipex file1 cmd1 cmd2 file2

int main(int ac, char **av, char **env)
{
	int ffile = STDIN_FILENO;
	int sfile = STDOUT_FILENO;

	if (ac < 3 || ac > 5)
	{
		perror("wrong arguments\n");
		exit(EXIT_FAILURE);
	}

	else if (ac == 5)
	{
		ffile = -1;
		sfile = -1;
	}

	else if (ac == 4)
	{
		if (!iscmd(av[1], env) && iscmd(av[2], env) && !iscmd(av[3], env))
			ffile = -1;
		else
			return -1;
	}


	pipex(ac, av, env, ffile, sfile);

	return 0;
}
