/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguerrer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 17:20:18 by aguerrer          #+#    #+#             */
/*   Updated: 2021/06/28 17:22:00 by aguerrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_putstr_fd(char *s, int fd)
{
	int	len;

	if (s == NULL || fd < 0)
		return (-1);
	len = ft_strlen(s);
	len = write(fd, s, len);
	return (len);
}
