/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguerrer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 18:00:53 by aguerrer          #+#    #+#             */
/*   Updated: 2021/06/25 19:06:49 by aguerrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static void	ft_strdelete(char **r_fd)
{
	if (r_fd != NULL && *r_fd != NULL)
	{
		free(*r_fd);
		*r_fd = NULL;
	}
}

static int	ft_readline(int fd, char **line, char **r_fd)
{
	int		len;
	char	*aux;

	len = 0;
	while (r_fd[fd][len] != '\n')
		len++;
	*line = ft_substr(*(r_fd + fd), 0, len);
	aux = ft_strdup(&r_fd[fd][len + 1]);
	free(*(r_fd + fd));
	*(r_fd + fd) = aux;
	return (1);
}

static int	ft_return(int fd, char **line, int n_bytes, char **r_fd)
{
	if (n_bytes < 0)
		return (-1);
	else if (n_bytes == 0 && (*(r_fd + fd) == NULL || r_fd[fd][0] == '\0'))
	{
		*line = ft_strdup("");
		ft_strdelete(&*(r_fd + fd));
		return (0);
	}
	else if (ft_strchr(*(r_fd + fd), '\n'))
		return (ft_readline(fd, line, r_fd));
	else
	{
		*line = ft_strdup(*(r_fd + fd));
		ft_strdelete(&*(r_fd + fd));
		return (0);
	}
}

static void	ft_check(char *buff, int n_bytes, char **r_fd, int fd)
{
	char	*var;

	var = NULL;
	*(buff + n_bytes) = '\0';
	if (*(r_fd + fd) == NULL)
		*(r_fd + fd) = ft_strdup(buff);
	else
	{
		var = ft_strjoin(*(r_fd + fd), buff);
		free(*(r_fd + fd));
		*(r_fd + fd) = var;
	}
}

int	get_next_line(int fd, char **line)
{
	char		*buff;
	int			n_bytes;
	static char	*r_fd[FD_SETSIZE];

	if (fd < 0 || line == NULL || BUFFER_SIZE == 0)
		return (-1);
	buff = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buff == NULL)
		return (-1);
	n_bytes = read(fd, buff, BUFFER_SIZE);
	while (n_bytes > 0)
	{
		ft_check(buff, n_bytes, r_fd, fd);
		if (ft_strchr(*(r_fd + fd), '\n'))
			break ;
		n_bytes = read(fd, buff, BUFFER_SIZE);
	}
	free(buff);
	return (ft_return(fd, &*line, n_bytes, r_fd));
}
