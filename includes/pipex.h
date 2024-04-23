/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:43:17 by aamirkha          #+#    #+#             */
/*   Updated: 2024/04/23 16:52:57 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "ft_printf.h"
# include "get_next_line.h"
# include <errno.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

# define PERMISSIONS 0644
# define MIN_ARGS_ALLOWED 5

typedef struct s_env
{
	char	**env;
	char	**newenv;
}			t_env;

enum		e_e
{
	FIRST = 0,
	SECOND = 1,
	READ = 0,
	WRITE = 1,
	LAST = 1,
	HERE_DOC = 2,
	APPEND = 4,
	LIMITER = 2
};

int			open_file(char *name, int mode);
void		pipex(int ac, char **av, char **env);
void		pipex_free(char **cmd, char **newenv);
void		close_pipes(int *_pipes);
t_env		env_init(char **env);
void		wait_for_all(void);

void		_exec(char *avcmd, t_env _env);
void		makepipe(char *avcmd, t_env _env, int mode);
void		makepipe_wrapper(int ac, char **av, int *_files, t_env _env);
void		here_doc_get(char **av, int *_pipe);
void		here_doc(char **av);

char		*get_path(char **env);
char		**__slice(char *path);
char		**cmd_handle(char *avcmd, char **newenv);

char		*cmd_lookup(char *cmd, char **newenv);
char		*current_lookup(char *cmd, char *path);
char		*ft_append_pipex(char *left, char *right);
int			iscmd(char *cmd, char **newenv);
char		*is_script(char *avcmd);

void		__terminate(char *err);

#endif // PIPEX_H
