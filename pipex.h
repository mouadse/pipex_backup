/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 23:12:55 by msennane          #+#    #+#             */
/*   Updated: 2024/08/02 15:23:29 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./get_next_line/get_next_line.h"
# include "data.h"
# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define SUCCESS 1
# define FAILURE 0

int		cleanup_pipe_resources(t_pipex *pipex);
int		deallocate_string_array(char **array);
int		cleanup_pipex_resources(t_pipex *pipex);

void	redirect_io(t_pipex pipex, int input, int output);
void	execute_child_process(t_pipex pipex, int command_index, int input,
			int output);
void	manage_child_processes(t_pipex pipex, int index);

int		is_valid_command(t_pipex *pipex, char *command_path, int index);
void	resolve_command_path(t_pipex *pipex, int index);
void	extract_path_environment(t_pipex *pipex);
void	open_input_output_files(t_pipex *pipex);
int		initialize_pipex_structure(t_pipex *pipex);

void	print_eof_warning(const char *delimiter);
void	process_heredoc_input(t_pipex *pipex);
void	setup_heredoc_files(t_pipex *pipex);

int		initialize_pipe_array(t_pipex *pipex);
int		allocate_process_id_array(t_pipex *pipex);
int		wait_for_child_processes(t_pipex *pipex);
int		execute_command_pipeline(t_pipex *pipex);

int		allocate_command_structures(t_pipex *pipeline);
int		initialize_pipeline(t_pipex *pipex, int argc, char **argv, char **envp);

void	cmd_not_found_error(t_pipex *pipex, int index);

int		allocate_command_structures_bonus(t_pipex *pipeline);
int		initialize_pipeline_bonus(t_pipex *pipex, int argc, char **argv,
			char **envp);

#endif
