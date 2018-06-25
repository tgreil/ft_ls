/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_manag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 10:24:11 by tgreil            #+#    #+#             */
/*   Updated: 2018/06/25 11:30:53 by tgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			list_add(t_list_manag *list, char *name)
{
	t_list_ls	*new;

	if (!(new = malloc(sizeof(t_list_ls))))
		return (E_ERROR);
	new->prev = NULL;
	new->next = NULL;
	new->name = name;
	list->list_len++;
	if (list->end)
	{
		list->end->next = new;
		new->prev = list->end;
		list->end = new;
	}
	else
	{
		list->start = new;
		list->end = new;
	}
	return (E_SUCCESS);
}
