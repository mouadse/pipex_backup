/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 22:52:05 by msennane          #+#    #+#             */
/*   Updated: 2024/08/02 15:49:15 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_eof_warning(const char *delimiter)
{
	write(1, "\n", 1);
	write(1, "EOF warning: wanted \"", 21);
	write(1, delimiter, ft_strlen(delimiter));
	write(1, "\"\n", 2);
}

void	process_heredoc_input(t_pipex *pipex)
{
	char	*input_line;
	char	*delimiter;

	delimiter = pipex->argv[2];
	while (1)
	{
		write(1, "pipex heredoc> ", 15);
		input_line = get_next_line(STDIN_FILENO);
		if (input_line == NULL || *input_line == '\0')
		{
			print_eof_warning(delimiter);
			break ;
		}
		if (ft_strlen(delimiter) == ft_strlen(input_line) - 1
			&& ft_strncmp(delimiter, input_line, ft_strlen(delimiter)) == 0)
			break ;
		write(pipex->infile_fd, input_line, ft_strlen(input_line) - 1);
		write(pipex->infile_fd, "\n", 1);
		free(input_line);
	}
	free(input_line);
}

void	setup_heredoc_files(t_pipex *pipex)
{
	const char	*heredoc_filename;

	heredoc_filename = ".here_doc";
	pipex->infile_fd = open(heredoc_filename, O_CREAT | O_WRONLY | O_TRUNC,
			0000644);
	if (pipex->infile_fd == -1)
		ft_putstr_fd("Error: failed to create heredoc file\n", STDERR_FILENO);
	process_heredoc_input(pipex);
	close(pipex->infile_fd);
	pipex->infile_fd = open(heredoc_filename, O_RDONLY);
	if (pipex->infile_fd == -1)
	{
		unlink(heredoc_filename);
		ft_putstr_fd("Error: failed to open heredoc file\n", STDERR_FILENO);
	}
	pipex->outfile_fd = open(pipex->argv[pipex->size + 3],
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (pipex->outfile_fd == -1)
	{
		if (access(pipex->argv[pipex->size + 2], W_OK) != 0)
			ft_putstr_fd("Error: permission denied\n", STDERR_FILENO);
		else
			ft_putstr_fd("Error: outfile undefined\n", STDERR_FILENO);
	}
}
