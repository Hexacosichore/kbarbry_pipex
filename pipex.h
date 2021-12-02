/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarbry <kbarbry@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 00:52:24 by kbarbry           #+#    #+#             */
/*   Updated: 2021/12/02 03:15:15 by kbarbry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

# define BUFFER_SIZE 42

//struct

typedef struct s_pipex
{
	int		f1;
	int		f2;
	int		pipe_fd[2];
	int		infile_pos;
	int		here_doc;
	char	*outfile;
	int		ac;
	char	**av;
	char	**env;
	int		fd_status;
	char	*cmd1;
	char	**cmd1_args;
	char	*cmd2;
	char	**cmd2_args;
}				t_pipex;

//pipex

int		pipex(t_pipex *data);

//utilities

char	**ft_split(const char *str, char c);
size_t	ft_strlen(const char *s);
char	*ft_calloc(int size);
char	*ft_strlcatgnl(char *str1, char *str2, int mode);
int		ft_putstr_fd(char *s, int fd, t_pipex *data);
int		ft_memcmp(const void *s1, const void *s2, size_t n);

//parsing

char	**parse_path(char **env);
char	*ft_find_path(char *cmd, char **env);
void	ft_free_split(char **split);
void	ft_free_all(t_pipex *data);

//bonus

int		pipex_bonus(t_pipex *data);

char	*get_next_line(int fd);
void	fd_here_doc(t_pipex *data, char *line);
void	child_process(char *av, t_pipex *data);
void	ft_execute(char *av, t_pipex *data);

#endif
