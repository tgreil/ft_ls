/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_manag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 10:24:11 by tgreil            #+#    #+#             */
/*   Updated: 2018/06/25 17:40:24 by tgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		list_sort(t_list_manag *list, int sens)
{
	t_list_ls	tmp;

	list->act = list->start;
	while (list->act)
	{
		if (list->act->prev &&
			((!sens && ft_strcmp(list->act->prev->name, list->act->name) > 0) ||
			(sens && ft_strcmp(list->act->prev->name, list->act->name) < 0)))
		{
			ft_memcpy(&tmp, list->act->prev, sizeof(t_list_ls) - 8 * 2);
			ft_memcpy(list->act->prev, list->act, sizeof(t_list_ls) - 8 * 2);
			ft_memcpy(list->act, &tmp, sizeof(t_list_ls) - 8 * 2);
			list->act = list->start;
		}
		else
			list->act = list->act->next;
	}
}

int			list_apply(t_list_manag *list,
					int (*f)(t_list_manag *, t_list_ls *, unsigned int flag),
															unsigned int flag)
{
	list->act = list->start;
	while (list->act)
	{
		if (f(list, list->act, flag) == E_ERROR)
			return (E_ERROR);
		list->act = list->act->next;
	}
	return (E_SUCCESS);
}

t_list_ls	*list_create(char *name)
{
	t_list_ls	*new;

	if (!(new = malloc(sizeof(t_list_ls))))
		return (NULL);
	new->prev = NULL;
	new->next = NULL;
	new->from = NULL;
	new->name = name;
	new->name_malloced = FALSE;
	new->name_len = ft_strlen(name);
	new->state = stat(new->name, &new->stat);
	return (new);
}

int			list_insert(t_list_ls *elem, char *name)
{
	t_list_ls	*new;

	if (!(new = list_create(name)))
		return (E_ERROR);
	new->next = elem->next;
	if (elem->next)
		elem->next->prev = new;
	new->prev = elem;
	elem->next = new;
	new->from = elem;
	new->name_malloced = TRUE;
	return (E_SUCCESS);
}

int			list_add(t_list_manag *list, char *name)
{
	t_list_ls	*new;

	if (!(new = list_create(name)))
		return (E_ERROR);
	list->list_len++;
	if (new->state < 0)
	{
		ft_printf("!2!%s%s: Problem to load file\n", LS_ERROR_MSG, new->name);
		list->list_len--;
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
