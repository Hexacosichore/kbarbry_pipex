/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarbry <kbarbry@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 04:44:53 by kbarbry           #+#    #+#             */
/*   Updated: 2021/12/02 05:37:00 by kbarbry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

/*=================================================

In this pipex, each time we have to leave the
programms for an error, we go throught this putstr
which unlink our outfile, close all fd, and free
everything for avoid leaks.

===================================================*/

int	ft_putstr_fd(char *s, int fd, t_pipex *data)
{
	int	i;

	i = 0;
	close(0);
	while (s && s[i])
		write(fd, &s[i++], 1);
	write(fd, "\n", 1);
	unlink(data->outfile);
	close(data->f1);
	close(data->f2);
	ft_free_all(data);
	exit(0);
	return (0);
}

// Some basics libft functions.

char	*ft_calloc(int size)
{
	int		i;
	char	*str;

	i = 0;
	str = (char *)malloc(sizeof(char) * size);
	if (!str)
		return (NULL);
	while (i < size)
		str[i++] = '\0';
	return (str);
}

size_t	ft_strlen(const char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strlcatgnl(char *str1, char *str2, int mode)
{
	char	*dest;
	int		i[4];

	i[0] = 0;
	while (str1 && str1[i[0]])
		i[0]++;
	i[1] = 0;
	while (str2 && str2[i[1]])
		i[1]++;
	if (i[0] + i[1] == 0)
		return (NULL);
	dest = (char *)ft_calloc(i[0] + i[1] + 1);
	if (!dest)
		return (str1);
	i[2] = 0;
	while (str1 && str1[i[2]] && i[2]++ >= 0)
		dest[i[2] - 1] = str1[i[2] - 1];
	i[3] = 0;
	while (str2 && str2[i[3]] && i[3]++ >= 0)
		dest[i[2] + i[3] - 1] = str2[i[3] - 1];
	dest[i[2] + i[3]] = '\0';
	if (mode == 1)
		free(str1);
	return (dest);
}

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned int	i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	if (!s1 || !s2)
		return (1);
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if (n < 1)
		return (1);
	while (i < n - 1 && str1[i] == str2[i])
		i++;
	return (str1[i] - str2[i]);
}
