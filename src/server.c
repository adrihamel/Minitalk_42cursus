/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguerrer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 17:55:50 by aguerrer          #+#    #+#             */
/*   Updated: 2021/06/25 18:52:07 by aguerrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_msg		g_msg;

char	*alloc_char(char c)
{
	char	*p;

	p = (char *)malloc(sizeof(char));
	if (p == NULL)
	{
		ft_putstr_fd("fatal error!\n", STDERR_FILENO);
		exit(1);
	}
	*p = c;
	return (p);
}

void	init_msg(void)
{
	char	*line;

	g_msg.msg = NULL;
	g_msg.buf = 0;
	g_msg.bit_cnt = 0;
	g_msg.client_pid = 0;
	ft_putstr_fd("Escribe el PID del cliente:\n", STDOUT_FILENO);
	get_next_line(STDIN_FILENO, &line);
	g_msg.client_pid = ft_atoi(line);
	free(line);
	kill(g_msg.client_pid, SIGUSR1);
}

void	print_msg(void)
{
	t_list	*list;

	ft_putstr_fd("Mensaje recibido: [", STDOUT_FILENO);
	list = g_msg.msg;
	while (list != NULL)
	{
		ft_putchar_fd(*(char *)list->content, STDOUT_FILENO);
		list = list->next;
	}
	ft_putstr_fd("]\n", STDOUT_FILENO);
}

void	signal_handler(int signo)
{
	g_msg.bit_cnt++;
	g_msg.buf = (g_msg.buf << 1) | (signo == SIGUSR1);
	usleep(50);
	if (signo == SIGUSR1)
		kill(g_msg.client_pid, SIGUSR1);
	else
		kill(g_msg.client_pid, SIGUSR2);
	if (g_msg.bit_cnt == 8)
	{
		ft_lstadd_back(&(g_msg.msg), ft_lstnew(alloc_char(g_msg.buf)));
		if (g_msg.buf == '\0')
		{
			print_msg();
			ft_lstclear(&(g_msg.msg), free);
			init_msg();
		}
		g_msg.bit_cnt = 0;
		g_msg.buf = 0;
	}
}

int	main(void)
{
	ft_putstr_fd("PID Servidor:", STDOUT_FILENO);
	ft_putnbr_fd(getpid(), STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	init_msg();
	while (1)
		pause();
}
