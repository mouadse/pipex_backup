/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 22:52:33 by msennane          #+#    #+#             */
/*   Updated: 2024/07/20 02:01:43 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	is_valid_command(t_pipex *pipex, char *command_path, int index)
{
	if (!command_path)
		return (FAILURE);
	if (access(command_path, F_OK) == 0)
	{
		pipex->cmd_list[index].exec_path = ft_strdup(command_path);
		if (!pipex->cmd_list[index].exec_path)
			return (FAILURE);
		pipex->cmd_list[index].is_found = SUCCESS;
		free(command_path);
		return (SUCCESS);
	}
	if (access(command_path, F_OK) == 0 && ft_strncmp(command_path, "/",
			1) == 0)
	{
		pipex->cmd_list[index].exec_path = ft_strdup(command_path);
		if (!pipex->cmd_list[index].exec_path)
			return (FAILURE);
		pipex->cmd_list[index].is_found = SUCCESS;
		free(command_path);
		return (SUCCESS);
	}
	free(command_path);
	return (FAILURE);
}

void	resolve_command_path(t_pipex *pipex, int index)
{
	int		path_index;
	char	*full_command_path;

	if (pipex->cmd_list[index].args_list[0] && is_valid_command(pipex,
			ft_strdup(pipex->cmd_list[index].args_list[0]), index))
		return ;
	if (!pipex->paths)
	{
		cmd_not_found_error(pipex, index);
		return ;
	}
	path_index = 0;
	while (pipex->paths[path_index])
	{
		full_command_path = ft_strjoin_three(pipex->paths[path_index], "/",
				pipex->cmd_list[index].args_list[0]);
		if (is_valid_command(pipex, full_command_path, index))
			break ;
		path_index++;
		if (!pipex->paths[path_index])
			cmd_not_found_error(pipex, index);
	}
}

void	extract_path_environment(t_pipex *pipex)
{
	int	env_index;

	env_index = 0;
	if (!pipex->envp)
		return ;
	while (pipex->envp[env_index] && ft_strncmp(pipex->envp[env_index], "PATH",
			4))
		env_index++;
	if (pipex->envp[env_index] && ft_strncmp(pipex->envp[env_index], "PATH",
			4) == 0)
		pipex->paths = ft_split(pipex->envp[env_index] + 5, ':');
}

void	open_input_output_files(t_pipex *pipex)
{
	pipex->infile_fd = open(pipex->argv[1], O_RDONLY, 0644);
	if (-1 == pipex->infile_fd)
		perror(pipex->argv[1]);
	pipex->outfile_fd = open(pipex->argv[pipex->size + 2],
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (-1 == pipex->outfile_fd)
		perror(pipex->argv[pipex->size + 2]);
}

int	initialize_pipex_structure(t_pipex *pipex)
{
	int	cmd_index;

	extract_path_environment(pipex);
	if (pipex->here_doc)
		setup_heredoc_files(pipex);
	else
		open_input_output_files(pipex);
	cmd_index = 0;
	while (cmd_index < pipex->size)
	{
		pipex->cmd_list[cmd_index].is_found = FAILURE;
		pipex->cmd_list[cmd_index].args_list = ft_split(pipex->argv[cmd_index
				+ 2 + pipex->here_doc], ' ');
		if (!pipex->cmd_list[cmd_index].args_list)
			return (FAILURE);
		if (!(cmd_index == 0 && pipex->infile_fd == -1)
			&& !(cmd_index == pipex->size - 1 && pipex->outfile_fd == -1))
			resolve_command_path(pipex, cmd_index);
		cmd_index++;
	}
	return (SUCCESS);
}
