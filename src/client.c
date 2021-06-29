/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguerrer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 17:28:38 by aguerrer          #+#    #+#             */
/*   Updated: 2021/06/28 17:30:06 by aguerrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include "utils.h"

int			g_flag;

void		signal_handle(int signo)
{
	if (signo == SIGUSR1)
		g_flag = 1;
	else if (signo == SIGUSR2)
		g_flag = 0;
	else
		g_flag = -1;
}

int			is_bit_set(int idx, char buf)
{
	char	mask;

	mask = 1 << (7 - idx);
	return ((buf & mask) != 0);
}

void		send_null(pid_t pid)
{
	int		i;

	i = 0;
	while (i < 8)
	{
		kill(pid, SIGUSR2);
		pause();
		if (g_flag != 0)
		{
			ft_putendl_fd("fatal error!", STDERR_FILENO);
			exit(1);
		}
		i++;
	}
}

void		send_msg(pid_t pid, char *str, int i, int j)
{
	char	buf;
	int		flag;

	pause();
	while (str[i])
	{
		buf = str[i];
		j = -1;
		while (++j < 8)
		{
			flag = is_bit_set(j, buf);
			usleep(50);
			if (flag == 1)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			pause();
			if ((flag != g_flag)
					&& ft_putstr_fd("fatal error!\n", STDERR_FILENO))
				exit(1);
		}
		i++;
	}
	send_null(pid);
	ft_putstr_fd("Mensaje enviado !\n", STDOUT_FILENO);
}

int			main(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (argc != 3)
	{
		ft_putstr_fd("Debe introducir el PID del servidor", STDERR_FILENO);
		ft_putstr_fd("y el mensaje a enviar\n", STDERR_FILENO);
		return (1);
	}
	if (argv[2][0] == '\0')
	{
		ft_putstr_fd("No se puede enviar cadena vacia.\n", STDERR_FILENO);
		return (1);
	}
	ft_putstr_fd("PID cliente:", STDOUT_FILENO);
	ft_putnbr_fd(getpid(), STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	signal(SIGUSR1, signal_handle);
	signal(SIGUSR2, signal_handle);
	send_msg(ft_atoi(argv[1]), argv[2], i, j);
}
