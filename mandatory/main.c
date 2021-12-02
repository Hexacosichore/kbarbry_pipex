/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarbry <kbarbry@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 00:52:54 by kbarbry           #+#    #+#             */
/*   Updated: 2021/12/02 01:07:58 by kbarbry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

// Initialising everything in data

static void	ft_init_data(t_pipex *data, int ac, char **av, char **env)
{
	data->f1 = open(av[1], O_RDONLY);
	data->f2 = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0666);
	data->env = env;
	data->av = av;
	data->ac = ac;
	data->cmd1 = av[2];
	data->cmd2 = av[3];
	data->cmd1_args = ft_split(data->cmd1, ' ');
	data->cmd2_args = ft_split(data->cmd2, ' ');
	if (!data->cmd1_args || !data->cmd2_args)
		ft_putstr_fd("Cmd or args error.", 2, data);
	data->outfile = av[ac - 1];
	if (data->f1 < 0 || data->f2 < 0)
		ft_putstr_fd("File access error.", 2, data);
}

//Just for free everything when we leave the program.

void	ft_free_all(t_pipex *data)
{
	ft_free_split(data->cmd2_args);
	ft_free_split(data->cmd1_args);
	free(data);
}

/*=================== Intro ======================

Pipex consists of reproducing the comportement
of a pipe "|" in shell langage. It means we have
to parse cmds and theirs args, and execute each
of them. For the mandatory part we just have to
handle 2 cmds. We take the input from infile
and we output the result in outfile.

./pipex infile cmd1 cmd2 outfile

===================================================*/

int	main(int ac, char **av, char **env)
{
	t_pipex	*data;

	data = (t_pipex *)ft_calloc(sizeof(t_pipex));
	if (ac != 5 || !data)
		return (write(2, "Usage : ./pipex in_file cmd1 cmd2 out_file.\n", 44));
	ft_init_data(data, ac, av, env);
	pipex(data);
	if (close(data->f1) < 0 || close(data->f2) < 0)
		ft_putstr_fd("Close error.", 2, data);
	ft_free_all(data);
	return (1);
}

/*================== Free Part ====================

For no leaks don't forget to free :

- data->cmd1_args
- data->cmd2_args
- data

===================================================*/