/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_init_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 23:18:18 by msennane          #+#    #+#             */
/*   Updated: 2024/08/04 12:01:13 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	allocate_command_structures_bonus(t_pipex *pipeline)
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

int	initialize_pipeline_bonus(t_pipex *pipex, int argc, char **argv,
		char **envp)
{
	pipex->argv = argv;
	pipex->envp = envp;
	pipex->here_doc = FAILURE;
	pipex->paths = NULL;
	pipex->infile_fd = -1;
	pipex->outfile_fd = -1;
	pipex->cmd_list = NULL;
	pipex->pids = NULL;
	pipex->pipes = NULL;
	pipex->exit_status = EXIT_SUCCESS;
	if (ft_strncmp(pipex->argv[1], "here_doc", 9) == 0
		&& ft_strncmp(pipex->argv[0], "./pipex_bonus", 14) == 0)
		pipex->here_doc = SUCCESS;
	pipex->size = argc - 3 - pipex->here_doc;
	if (!allocate_command_structures_bonus(pipex))
		return (FAILURE);
	return (SUCCESS);
}
