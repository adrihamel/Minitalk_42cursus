/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguerrer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 17:32:31 by aguerrer          #+#    #+#             */
/*   Updated: 2021/06/28 17:34:07 by aguerrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;
	t_list	*aux;

	aux = *lst;
	while (aux)
	{
		temp = aux->next;
		del(aux->content);
		free(aux);
		aux = temp;
	}
	*lst = NULL;
}
