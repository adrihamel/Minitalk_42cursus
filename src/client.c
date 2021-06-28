/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguerrer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 18:39:50 by aguerrer          #+#    #+#             */
/*   Updated: 2021/06/28 20:36:43 by aguerrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <signal.h>
#include <stdio.h>

int			g_flag;

void	signal_handle(int signo)
{
	if (signo == SIGUSR1)
		g_flag = 1;
	else if (signo == SIGUSR2)
		g_flag = 0;
}

int	is_bit_set(int idx, char buf)
{
	char	mask;

	mask = 1 << (7 - idx);
	return ((buf & mask) != 0);
}

void	send_null(pid_t pid)
{
	int		i;

	i = 0;
	while (i < 8)
	{
		kill(pid, SIGUSR2);
		pause();
		if (g_flag == 1)
		{
			ft_putendl_fd("¡ Fatal Error !", STDERR_FILENO);
			exit(1);
		}
		i++;
	}
}

void	send_msg(pid_t pid, char *str)
{
	char	buf;
	int		i;
	int		j;
	int		flag;

	pause();
	i = 0;
	while (*(str + i))
	{
		buf = *(str + i++);
		j = -1;
		while (++j < 8)
		{
			flag = is_bit_set(j, buf);
			if (flag == 1)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			pause();
			if ((flag != g_flag))
				exit(1);
		}
	}
	send_null(pid);
	ft_putstr_fd("Mensaje enviado correctamente\n", STDOUT_FILENO);
}

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		ft_putstr_fd("Debe introducir el PID del servidor", 2);
		ft_putstr_fd("y el mensaje a enviar", 2);
		return (1);
	}
	if (argv[2][0] == '\0')
	{
		ft_putstr_fd("No se puede enviar cadena vacia\n", 2);
		return (1);
	}
	ft_putstr_fd("PID cliente:", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	signal(SIGUSR1, signal_handle);
	signal(SIGUSR2, signal_handle);
	send_msg(ft_atoi(argv[1]), argv[2]);
}
