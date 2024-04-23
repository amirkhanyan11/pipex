/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:46:45 by aamirkha          #+#    #+#             */
/*   Updated: 2024/04/23 16:49:24 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*is_script(char *avcmd)
{
	return (ft_strchr(avcmd, '/'));
}

void	__terminate(char *err)
{
	perror(err);
	exit(EXIT_FAILURE);
}
