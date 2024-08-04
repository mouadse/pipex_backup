/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 22:52:20 by msennane          #+#    #+#             */
/*   Updated: 2024/07/20 01:24:42 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	validate_arguments(int argc)
{
	if (argc != 5)
	{
		ft_putstr_fd("Error: Invalid number of arguments\n", 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	initialize(t_pipex *pipex, int argc, char **argv, char **envp)
{
	if (initialize_pipeline(pipex, argc, argv, envp) == FAILURE)
	{
		ft_putstr_fd("Error: Failed to initialize pipeline\n", 2);
		return (cleanup_pipex_resources(pipex), EXIT_FAILURE);
	}
	if (initialize_pipex_structure(pipex) == FAILURE)
	{
		ft_putstr_fd("Error: Failed to initialize pipex structure\n", 2);
		return (cleanup_pipex_resources(pipex), EXIT_FAILURE);
	}
	if (!initialize_pipe_array(pipex))
	{
		ft_putstr_fd("Error: Failed to initialize pipe array\n", 2);
		return (cleanup_pipex_resources(pipex), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	execute_and_cleanup(t_pipex *pipex)
{
	if (!execute_command_pipeline(pipex))
	{
		ft_putstr_fd("Error: Failed to execute command pipeline\n", 2);
		return (cleanup_pipex_resources(pipex), pipex->exit_status);
	}
	if (!cleanup_pipex_resources(pipex))
	{
		ft_putstr_fd("Error: Failed to cleanup pipex resources\n", 2);
		return (EXIT_FAILURE);
	}
	return (pipex->exit_status);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		status;

	status = validate_arguments(argc);
	if (status != EXIT_SUCCESS)
		return (status);
	status = initialize(&pipex, argc, argv, envp);
	if (status != EXIT_SUCCESS)
		return (status);
	return (execute_and_cleanup(&pipex));
}
