/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 22:52:45 by msennane          #+#    #+#             */
/*   Updated: 2024/08/04 11:10:51 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	redirect_io(t_pipex pipex, int input, int output)
{
	int	stdin_dup_ret;
	int	stdout_dup_ret;

	stdin_dup_ret = dup2(input, STDIN_FILENO);
	if (-1 == stdin_dup_ret)
	{
		cleanup_pipe_resources(&pipex);
		cleanup_pipex_resources(&pipex);
		exit(EXIT_FAILURE);
	}
	(void)close(input);
	stdout_dup_ret = dup2(output, STDOUT_FILENO);
	if (-1 == stdout_dup_ret)
	{
		cleanup_pipe_resources(&pipex);
		cleanup_pipex_resources(&pipex);
		exit(EXIT_FAILURE);
	}
	(void)close(output);
}

void	print_error_and_exit(t_pipex *pipex, char *exec_path, char *arg0,
		int error_code)
{
	if (error_code == 126)
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		ft_putstr_fd(arg0, STDERR_FILENO);
		if (open(exec_path, O_DIRECTORY) != -1)
			ft_putstr_fd(": is a directory\n", STDERR_FILENO);
		else
			ft_putstr_fd(": permission denied\n", STDERR_FILENO);
	}
	else if (error_code == 127)
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		ft_putstr_fd(arg0, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
	}
	cleanup_pipex_resources(pipex);
	exit(error_code);
}

void	execute_child_process(t_pipex pipex, int command_index, int input,
		int output)
{
	char	*exec_path;
	char	**args_list;

	exec_path = pipex.cmd_list[command_index].exec_path;
	args_list = pipex.cmd_list[command_index].args_list;
	redirect_io(pipex, input, output);
	cleanup_pipe_resources(&pipex);
	if (!exec_path || !args_list)
	{
		cleanup_pipex_resources(&pipex);
		exit(127);
	}
	if (open(exec_path, O_DIRECTORY) != -1 || (access(exec_path, F_OK) == 0
			&& access(exec_path, X_OK) == -1))
	{
		print_error_and_exit(&pipex, exec_path, args_list[0], 126);
	}
	if (execve(exec_path, args_list, pipex.envp) == -1)
	{
		print_error_and_exit(&pipex, exec_path, args_list[0], 127);
	}
}

void	manage_child_processes(t_pipex pipex, int index)
{
	if (!pipex.cmd_list[index].args_list)
	{
		cleanup_pipe_resources(&pipex);
		cleanup_pipex_resources(&pipex);
		exit(EXIT_FAILURE);
	}
	if (index == 0)
		execute_child_process(pipex, index, pipex.infile_fd,
			pipex.pipes[index][1]);
	else if (index != pipex.size - 1)
	{
		execute_child_process(pipex, index, pipex.pipes[index - 1][0],
			pipex.pipes[index][1]);
	}
	else
		execute_child_process(pipex, index, pipex.pipes[index - 1][0],
			pipex.outfile_fd);
}
