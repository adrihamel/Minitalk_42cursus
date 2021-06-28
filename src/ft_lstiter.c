/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguerrer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 17:31:12 by aguerrer          #+#    #+#             */
/*   Updated: 2021/06/28 17:31:34 by aguerrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (f == NULL || lst == 0)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
