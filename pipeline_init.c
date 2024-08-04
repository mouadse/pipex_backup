/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 22:52:27 by msennane          #+#    #+#             */
/*   Updated: 2024/07/12 22:52:28 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	allocate_command_structures(t_pipex *pipeline)
{
	int	i;

	pipeline->cmd_list = malloc(sizeof(t_command) * pipeline->size);
	if (!pipeline->cmd_list)
		return (FAILURE);
	i = 0;
	while (i < pipeline->size)
	{
		pipeline->cmd_list[i].args_list = NULL;
		pipeline->cmd_list[i].exec_path = NULL;
		pipeline->cmd_list[i].is_found = FAILURE;
		i++;
	}
	return (SUCCESS);
}

int	initialize_pipeline(t_pipex *pipex, int argc, char **argv, char **envp)
{
	pipex->argv = argv;
	pipex->envp = envp;
	pipex->here_doc = FAILURE;
	pipex->paths = NULL;
	pipex->infile_fd = -1;
	pipex->outfile_fd = -1;
	pipex->cmd_list = NULL;
	pipex->pids = NULL;
	pipex->exit_status = EXIT_SUCCESS;
	pipex->pipes = NULL;
	pipex->size = argc - 3;
	if (!allocate_command_structures(pipex))
		return (FAILURE);
	return (SUCCESS);
}
