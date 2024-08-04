/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 22:52:10 by msennane          #+#    #+#             */
/*   Updated: 2024/07/20 01:05:48 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	initialize_pipe_array(t_pipex *pipex)
{
	int	i;

	pipex->pipes = malloc(sizeof(int *) * pipex->size);
	if (!pipex->pipes)
		return (FAILURE);
	i = 0;
	while (i < pipex->size)
	{
		pipex->pipes[i] = malloc(sizeof(int) * 2);
		if (!pipex->pipes[i])
			return (FAILURE);
		if (pipe(pipex->pipes[i]) == -1)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

int	allocate_process_id_array(t_pipex *pipex)
{
	int	i;

	pipex->pids = malloc(sizeof(int) * pipex->size);
	if (!pipex->pids)
		return (FAILURE);
	i = 0;
	while (i < pipex->size)
	{
		pipex->pids[i] = -1;
		i++;
	}
	return (SUCCESS);
}

int	wait_for_child_processes(t_pipex *pipex)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (i < pipex->size && pipex->pids[i] > 0)
	{
		waitpid(pipex->pids[i], &status, 0);
		if (WIFEXITED(status))
			pipex->exit_status = WEXITSTATUS(status);
		i++;
	}
	return (SUCCESS);
}

int	execute_command_pipeline(t_pipex *pipex)
{
	int		i;
	pid_t	child_pid;

	if (!allocate_process_id_array(pipex))
		return (FAILURE);
	i = 0;
	while (i < pipex->size)
	{
		child_pid = fork();
		if (-1 == child_pid)
		{
			cleanup_pipe_resources(pipex);
			return (FAILURE);
		}
		else if (0 == child_pid)
			manage_child_processes(*pipex, i);
		else
			pipex->pids[i] = child_pid;
		i++;
	}
	cleanup_pipe_resources(pipex);
	wait_for_child_processes(pipex);
	return (SUCCESS);
}
