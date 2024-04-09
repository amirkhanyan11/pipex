

#include "pipex.h"


void handle_files(int ffile, int sfile)
{
	close(ffile);
	close(sfile);
}

int pipex(char **av, char **env)
{
	int fd[2];

	char **newenv = __slice(get_path(env));
	t_cmds cmds = cmd_handle(av, newenv);

	int ffile = open_file(av[1], 0);

	int sfile = open_file(av[4], 1);

	if (-1 == pipe(fd))
		mah(errno);

	int pid = fork();

	if (0 == pid) // child 1
	{
		dup2(ffile, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);

		close(fd[0]);
		close(fd[1]);

		handle_files(ffile, sfile);

		execve(cmds.left[0], cmds.left, env);
		pipex_free(cmds, fd, newenv);
		exit(EXIT_FAILURE);
	}

	

	int pid2 = fork();

	if (0 == pid2) // child 2
	{
		dup2(sfile, STDOUT_FILENO);
		dup2(fd[0], STDIN_FILENO);

		close(fd[0]);
		close(fd[1]);

		handle_files(ffile, sfile);

		execve(cmds.right[0], cmds.right, env);
		pipex_free(cmds, fd, newenv);
		exit(EXIT_FAILURE);
	}

	int status = 0;

	handle_files(ffile, sfile);
	pipex_free(cmds, fd, newenv);
	pipex_wait(pid, pid2, &status);

	return WEXITSTATUS(status);
}


// ./pipex file1 cmd1 cmd2 file2

int main(int ac, char **av, char **env)
{
	if (ac != 5)
	{
		perror ("Wrong arguments!\n");
		exit(EXIT_FAILURE);
	}

	int es = pipex(av, env);

	return es;
}
