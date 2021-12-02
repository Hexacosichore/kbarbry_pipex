/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarbry <kbarbry@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 00:08:18 by kbarbry           #+#    #+#             */
/*   Updated: 2021/12/02 05:40:21 by kbarbry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#include <string.h>

// fd here doc take the << input, and handle it as infile.

void	fd_here_doc(t_pipex *data, char *line)
{
	int		pipe_fd[2];
	pid_t	parent;

	if (pipe(pipe_fd) < 0)
		ft_putstr_fd("Pipe error.", 2, data);
	parent = fork();
	if (parent < 0)
		ft_putstr_fd("Fork error.", 2, data);
	if (parent == 0)
	{
		if (close(pipe_fd[0]) < 0)
			ft_putstr_fd("Close error.", 2, data);
		while (1)
		{
			write(1, "pipe heredoc> ", 15);
			line = get_next_line(0);
			if (!ft_memcmp(line, data->av[2], ft_strlen(line) - 1))
				exit(1);
			write(pipe_fd[1], line, ft_strlen(line));
		}
	}
	if (close(pipe_fd[1]) < 0)
		ft_putstr_fd("Close error.", 2, data);
	if (dup2(pipe_fd[0], 0) < 0)
		ft_putstr_fd("Dup2 error.", 2, data);
}

// Execute allow us to execv properly

void	ft_execute(char *av, t_pipex *data)
{
	char	**cmd_args;
	char	*path;

	cmd_args = ft_split(av, ' ');
	path = ft_find_path(cmd_args[0], data->env);
	if (execve(path, cmd_args, data->env) < 0)
	{
		free(cmd_args);
		free(path);
		ft_putstr_fd("Execution error.", 2, data);
	}
	free(cmd_args);
	free(path);
}

/*=================================================

Child process function will be our loop, each time
we call it, it create a pipe, a fork, and execute
one commands until there is no one left.

===================================================*/

void	child_process(char *av, t_pipex *data)
{
	int		pipe_fd[2];
	pid_t	parent;

	if (pipe(pipe_fd) < 0)
		ft_putstr_fd("Pipe error.", 2, data);
	parent = fork();
	if (parent < 0)
		ft_putstr_fd("Fork error.", 2, data);
	if (parent == 0)
	{
		if (close(pipe_fd[0]) < 0)
			ft_putstr_fd("Close error.", 2, data);
		if (dup2(pipe_fd[1], 1) < 0)
			ft_putstr_fd("Dup2 error.", 2, data);
		ft_execute(av, data);
	}
	else
	{
		if (close(pipe_fd[1]) < 0)
			ft_putstr_fd("Close error.", 2, data);
		if (dup2(pipe_fd[0], 0) < 0)
			ft_putstr_fd("Dup2 error.", 2, data);
		waitpid(parent, &data->fd_status, 0);
	}
}
