/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:22:03 by aamirkha          #+#    #+#             */
/*   Updated: 2024/04/23 16:59:34 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(int ac, char **av, char **env)
{
	t_env	_env;
	int		_files[2];

	_env = env_init(env);
	if (!ft_strncmp(av[1], "here_doc", ft_strlen(av[1])))
	{
		_files[WRITE] = open_file(av[ac - 1], WRITE | APPEND);
		here_doc(av);
	}
	else
	{
		_files[READ] = open_file(av[1], READ);
		dup2(_files[READ], STDIN_FILENO);
		_files[WRITE] = open_file(av[ac - 1], WRITE);
	}
	makepipe_wrapper(ac, av, _files, _env);
	if (!ft_strncmp(av[1], "here_doc", ft_strlen(av[1])))
		close(_files[READ]);
	close(_files[WRITE]);
	ft_free_split(_env.newenv);
	wait_for_all();
}

int	main(int ac, char **av, char **env)
{
	if (ac < MIN_ARGS_ALLOWED)
		__terminate("pipex: ./pipex infile cmd1 cmd2 outfile\n");
	pipex(ac, av, env);
	return (1);
}


int	main(int ac, char **av, char **env)
{
	if (ac != MIN_ARGS_ALLOWED)
		__terminate("pipex: ./pipex infile cmd1 cmd2 outfile\n");
	pipex(ac, av, env);
	return (1);
}
