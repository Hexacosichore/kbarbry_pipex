/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarbry <kbarbry@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 23:56:07 by kbarbry           #+#    #+#             */
/*   Updated: 2021/12/02 05:50:56 by kbarbry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

// Initialising everything in data

static void	ft_init_data(t_pipex *data, int ac, char **av, char **env)
{
	data->ac = ac;
	data->av = av;
	data->env = env;
	data->outfile = av[ac - 1];
	if (ft_memcmp(av[1], "here_doc", 8) == 0)
	{
		if (ac < 6)
			ft_putstr_fd("Usage : ./pipex here_doc LIMITER ... .\n", 2, data);
		data->here_doc = 1;
		data->infile_pos = 3;
		data->f2 = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
		data->f1 = open(av[data->infile_pos], O_RDONLY, 0777);
		fd_here_doc(data, NULL);
	}
	else
	{
		data->here_doc = 0;
		data->infile_pos = 2;
		data->f2 = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		data->f1 = open(av[1], O_RDONLY, 0777);
		if (dup2(data->f1, 0) < 0)
			ft_putstr_fd("Dup2 error or bad file.", 2, data);
	}
	if (!data->f1 || !data->f2)
		ft_putstr_fd("Open error.", 2, data);
}

//Just for free everything when we leave the program.

void	ft_free_all(t_pipex *data)
{
	free(data);
}

/*=================== Intro ======================

For this bonus we have to handle the here_doc infile
which means that we have to read from the standart input
and stop reading only when we found the LIMITER.
We also have to append the output on the output file
and not trunc it like with original pipex.

./pipex here_doc LIMITER cmd1 cmd2 ... cmdn outfile

If there is no here_doc arg, we just have to handle multi pipes.

./pipex infile cmd1 cmd2 ... cmdn outfile

===================================================*/

int	main(int ac, char **av, char **env)
{
	t_pipex	*data;

	data = (t_pipex *)ft_calloc(sizeof(t_pipex));
	if (ac < 5)
		return (write(2, "Usage : ./pipex in_file cmd1 cmd2 out_file.\n", 44));
	if (!data)
		return (write(2, "Malloc error.\n", 15));
	ft_init_data(data, ac, av, env);
	while (data->infile_pos < ac - 2)
		child_process(av[data->infile_pos++], data);
	if (dup2(data->f2, 1) < 0)
		ft_putstr_fd("Dup2 error.", 2, data);
	ft_execute(av[ac - 2], data);
	return (0);
}
