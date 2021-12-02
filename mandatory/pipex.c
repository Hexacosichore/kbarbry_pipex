/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarbry <kbarbry@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 03:31:33 by kbarbry           #+#    #+#             */
/*   Updated: 2021/12/02 05:39:42 by kbarbry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

// Child process is the first one called by pipex.

int	ft_child_process(t_pipex *data)
{
	char	*path_cmd;

	path_cmd = ft_find_path(data->cmd1_args[0], data->env);
	if (!path_cmd)
		ft_putstr_fd("Cmd1 not found.", 2, data);
	if (dup2(data->f1, 0) < 0 || dup2(data->pipe_fd[1], 1) < 0)
		ft_putstr_fd("Dup2 error.", 2, data);
	if (close(data->pipe_fd[1]) || close(data->pipe_fd[0]) < 0)
		ft_putstr_fd("Close error.", 2, data);
	if (execve(path_cmd, data->cmd1_args, data->env) == -1)
	{
		free(path_cmd);
		ft_putstr_fd("Cmd1 execution problem.", 2, data);
	}
	free(path_cmd);
	return (1);
}

// Then parent process is called.

int	ft_parent_process(t_pipex *data)
{
	char	*path_cmd;

	path_cmd = ft_find_path(data->cmd2_args[0], data->env);
	if (!path_cmd)
		ft_putstr_fd("Cmd2 not found.", 2, data);
	if (dup2(data->f2, 1) < 0 || dup2(data->pipe_fd[0], 0) < 0)
		ft_putstr_fd("Dup2 error.", 2, data);
	if (close(data->pipe_fd[0]) < 0 || close(data->pipe_fd[1]) < 0)
		ft_putstr_fd("Close error.", 2, data);
	if (execve(path_cmd, data->cmd2_args, data->env) == -1)
	{
		free(path_cmd);
		ft_putstr_fd("Cmd2 execution problem.", 2, data);
	}
	free(path_cmd);
	return (1);
}

/*=================================================

Pipex functions create a pipe, then fork the
program, and just call the child process first,
then call the parent process, and leaves
properly, or with an putstr error if anything
didn't works.

===================================================*/

int	pipex(t_pipex *data)
{
	pid_t	child1;
	pid_t	child2;

	if (pipe(data->pipe_fd) < 0)
		ft_putstr_fd("Pipe error.", 2, data);
	child1 = fork();
	if (child1 < 0)
		ft_putstr_fd("Fork error.", 2, data);
	if (child1 == 0)
		ft_child_process(data);
	child2 = fork();
	if (child2 < 0)
		ft_putstr_fd("Fork error.", 2, data);
	if (child2 == 0)
		ft_parent_process(data);
	if (close(data->pipe_fd[0]) || close(data->pipe_fd[1]) < 0)
		ft_putstr_fd("Close error.", 2, data);
	waitpid(child1, &(data->fd_status), 0);
	if (data->fd_status != 0)
		ft_putstr_fd("Fork closes.", 2, data);
	waitpid(child2, &(data->fd_status), 0);
	return (1);
}
