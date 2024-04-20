/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:43:17 by aamirkha          #+#    #+#             */
/*   Updated: 2024/04/20 19:04:34 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "ft_printf.h"
# include <errno.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_env
{
	char	**env;
	char	**newenv;
}			t_env;

enum e_e
{
	FIRST = 0,
	SECOND = 1,
	READ = 0,
	WRITE = 1
};

int			open_file(char *name, int mode);
void		pipex(int ac, char **av, char **env);
void		pipex_free(char **cmd, char **newenv);
void		pipex_wait(int pid, int pid2, int *status);
void		close_pipes(int *_pipes);
t_env		__env_arg(char **env, char **newenv);
// void 		childp(char *filename, int *_pipes, t_cmds *cmds, t_env _env);

char		*get_path(char **env);
char		**__slice(char *path);
char	**cmd_handle(char *avcmd, char **newenv);

char		*cmd_lookup(char *cmd, char **newenv);
char		*current_lookup(char *cmd, char *path);
char		*ft_append_pipex(char *left, char *right);
int			iscmd(char *cmd, char **newenv);

void		__terminate(int err);

#endif // PIPEX_H
