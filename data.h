/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 23:14:53 by msennane          #+#    #+#             */
/*   Updated: 2024/07/28 23:14:54 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

typedef struct s_command
{
	int			is_found;
	char		*exec_path;
	char		**args_list;
}				t_command;

typedef struct s_pipex
{
	char		**envp;
	char		**argv;
	int			size;
	int			here_doc;
	int			infile_fd;
	int			outfile_fd;
	char		**paths;
	int			*pids;
	int			**pipes;
	t_command	*cmd_list;
	int			exit_status;
}				t_pipex;

#endif
