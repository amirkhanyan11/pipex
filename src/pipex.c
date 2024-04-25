/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:22:03 by aamirkha          #+#    #+#             */
/*   Updated: 2024/04/25 15:36:39 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(int ac, char **av, char **env)
{
	t_env	_env;
	int		infile;
	int		outfile;

	_env = env_init(env);
	if (!ft_strncmp(av[1], "here_doc", ft_strlen(av[1])))
	{
		here_doc(av);
		outfile = open_file(av[ac - 1], O_RDWR | O_CREAT);
	}
	else
	{
		outfile = open_file(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC);
		infile = open_file(av[1], O_RDONLY);
		dup2(infile, STDIN_FILENO);
	}
	makepipe_wrapper(ac, av, outfile, _env);
	if (!ft_strncmp(av[1], "here_doc", ft_strlen(av[1])))
		close(infile);
	close(outfile);
	ft_free_split(_env.newenv);
	wait_for_all();
}

int	main(int ac, char **av, char **env)
{
	if (ac < MIN_ARGS_ALLOWED)
		__terminate("pipex: ./pipex infile cmd1 cmd2 outfile\n");
	pipex(ac, av, env);
	system("leaks pipex");
	return (1);
}
