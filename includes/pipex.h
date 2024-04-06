/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:43:17 by aamirkha          #+#    #+#             */
/*   Updated: 2024/04/06 16:55:14 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "ft_printf.h"
# include <errno.h>
# include <fcntl.h>


typedef struct s_cmd
{
	char **left;
	char **right;
}	t_cmds;


int open_file(char *name, int mode);
void pipex(int ac, char **av, char **env);
void pipex_free(t_cmds cmds, int * fd, char **newenv);
void pipex_wait(int pid, int pid2);

char *get_path(char **env);
char **__slice(char *path);
t_cmds cmd_handle(char **av, char **newenv);

char *cmd_lookup(char *cmd, char **newenv);
char *current_lookup(char *cmd, char *path);
char	*ft_append(char *left, char  * right);


void mah();


#endif // PIPEX_H
