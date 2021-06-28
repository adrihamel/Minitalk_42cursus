/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguerrer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 17:34:19 by aguerrer          #+#    #+#             */
/*   Updated: 2021/06/25 18:04:22 by aguerrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include "utils.h"
# include <signal.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_msg
{
	t_list		*msg;
	char		buf;
	int			bit_cnt;
	pid_t		client_pid;
}				t_msg;

#endif
