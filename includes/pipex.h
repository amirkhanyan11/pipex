/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:43:17 by aamirkha          #+#    #+#             */
/*   Updated: 2024/04/05 20:20:41 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "ft_printf.h"
#include <errno.h>

void child(char **cmd, char **newenv, int *fd, int fileno);
void pipex(int ac, char **av, char **env);
void pipex_free(char *c1, char *c2, char **newenv);
void pipex_wait(int *fd, int pid, int pid2);


char *get_path(char **env);
char **__slice(char *path);
int cmd_handle(char *cmd, char **env);

char *cmd_lookup(char *cmd, char **newenv);
char *current_lookup(char *cmd, char *path);
char	*ft_append(char *left, char  * right);


void mah();


#endif // PIPEX_H
