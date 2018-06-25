/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_manag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 10:24:11 by tgreil            #+#    #+#             */
/*   Updated: 2018/06/25 12:55:10 by tgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			list_apply(t_list_manag *list,
							int (*f)(t_list_manag *, t_list_ls *))
{
	list->act = list->start;
	while (list->act)
	{
		if (f(list, list->act) == E_ERROR)
			return (E_ERROR);
		list->act = list->act->next;
	}
	return (E_SUCCESS);
}

int			list_add(t_list_manag *list, char *name)
{
	t_list_ls	*new;

	if (!(new = malloc(sizeof(t_list_ls))))
		return (E_ERROR);
	new->prev = NULL;
	new->next = NULL;
	new->name = name;
	list->list_len++;
	if ((new->state = stat(new->name, &new->stat)) < 0)
	{
		ft_printf("!2!%s%s: Problem to load file\n", LS_ERROR_MSG, new->name);
		free(new);
	}
	else if (list->end)
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
