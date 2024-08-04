/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 22:52:59 by msennane          #+#    #+#             */
/*   Updated: 2024/07/19 21:55:57 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	cmd_not_found_error(t_pipex *pipex, int index)
{
	ft_putstr_fd("pipex: ", STDERR_FILENO);
	ft_putstr_fd(pipex->cmd_list[index].args_list[0], STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	pipex->cmd_list[index].is_found = FAILURE;
}
