/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarbry <kbarbry@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 03:58:40 by kbarbry           #+#    #+#             */
/*   Updated: 2021/12/02 01:27:03 by kbarbry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

// Usefull when leaving pipex or if an error occurs.

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

// Parse path allow us to grep the "PATH=..." line in env.

char	**parse_path(char **env)
{
	char	**path;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (ft_memcmp(env[i], "PATH=", 5))
		i++;
	while (env[i][j] != '=')
		j++;
	path = ft_split(&env[i][j + 1], ':');
	return (path);
}

/*=================================================

Find path tests each PATH possibilities, when the
right path is found, we take it, add "/" and the
commands, to have our executable path command.

return exemple : "/usr/local/bin/xx"

===================================================*/

char	*ft_find_path(char *cmd, char **env)
{
	int		i;
	char	**path;
	char	*cmd_path;

	i = 0;
	path = parse_path(env);
	cmd_path = NULL;
	while (access(cmd_path, X_OK) == -1 && path[i])
	{
		free(cmd_path);
		cmd_path = ft_strlcatgnl(path[i], "/", 0);
		cmd_path = ft_strlcatgnl(cmd_path, cmd, 1);
		i++;
	}
	if (access(cmd_path, X_OK) == -1)
		return (NULL);
	ft_free_split(path);
	return (cmd_path);
}

// Don't forget to free cmd_path to avoid leaks.