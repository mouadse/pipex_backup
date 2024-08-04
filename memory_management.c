/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 22:52:23 by msennane          #+#    #+#             */
/*   Updated: 2024/07/28 23:15:21 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	cleanup_pipe_resources(t_pipex *pipex)
{
	int	i;

	if (!pipex || !pipex->pipes)
		return (FAILURE);
	i = 0;
	while (i < pipex->size && pipex->pipes[i])
	{
		if (pipex->pipes[i])
		{
			close(pipex->pipes[i][0]);
			close(pipex->pipes[i][1]);
			free(pipex->pipes[i]);
		}
		i++;
	}
	free(pipex->pipes);
	if (-1 != pipex->infile_fd)
	{
		close(pipex->infile_fd);
	}
	if (-1 != pipex->outfile_fd)
	{
		close(pipex->outfile_fd);
	}
	return (SUCCESS);
}

int	deallocate_string_array(char **array)
{
	int	i;

	if (!array)
		return (FAILURE);
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (SUCCESS);
}

int	cleanup_pipex_resources(t_pipex *pipex)
{
	int	i;

	if (!pipex)
		return (FAILURE);
	i = 0;
	while (i < pipex->size)
	{
		deallocate_string_array(pipex->cmd_list[i].args_list);
		if (pipex->cmd_list[i].is_found)
			free(pipex->cmd_list[i].exec_path);
		i++;
	}
	free(pipex->cmd_list);
	if (pipex->paths)
		deallocate_string_array(pipex->paths);
	if (-1 != pipex->infile_fd)
		close(pipex->infile_fd);
	if (-1 != pipex->outfile_fd)
		close(pipex->outfile_fd);
	if (pipex->pids)
		free(pipex->pids);
	if (pipex->here_doc)
		unlink(".here_doc");
	return (SUCCESS);
}
