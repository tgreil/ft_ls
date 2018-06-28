/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_manag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 10:24:11 by tgreil            #+#    #+#             */
/*   Updated: 2018/06/28 17:21:55 by tgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		list_sort(t_list_manag *list, int sens,
									int (*f)(t_list_ls *, t_list_ls *))
{
	t_list_ls	tmp;

	list->act = list->start;
	while (list->act)
	{
		if (list->act->prev &&
			((!sens && f(list->act->prev, list->act) > 0) ||
			(sens && f(list->act->prev, list->act) < 0)))
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

t_list_ls	*list_create(t_list_manag *list, char *name)
{
	t_list_ls	*new;

	if (!(new = malloc(sizeof(t_list_ls))))
		return (NULL);
	ft_bzero(new, sizeof(t_list_ls));
	new->prev = NULL;
	new->next = NULL;
	if (!(new->name = ft_strdup(name)))
		return (NULL);
	if (list->path)
		new->name_pathed = ft_strjoin(list->path, name);
	else
		new->name_pathed = ft_strdup(name);
	new->state = stat(new->name_pathed, &new->stat);
	new->folder.list_len = 0;
	new->folder.path = NULL;
	new->folder.start = NULL;
	new->folder.end = NULL;
	new->folder.act = NULL;
	new->list = list;
	return (new);
}

int			list_calc(t_list_manag *list, t_list_ls *new)
{
	list->calc[0] += new->stat.st_blocks;
	if (list->calc[1] < int_get_unit(new->stat.st_nlink))
		list->calc[1] = int_get_unit(new->stat.st_nlink);
	if (list->calc[4] < int_get_unit(new->stat.st_size))
		list->calc[4] = int_get_unit(new->stat.st_size);
	return (E_SUCCESS);
}

int			list_add(t_list_manag *list, char *name)
{
	t_list_ls	*new;

	if (!(new = list_create(list, name)))
		return (E_ERROR);
	if (new->state < 0)
	{
		ft_printf("!2!%s%s: Problem to load file\n", LS_ERROR_MSG, new->name);
		free(new->name_pathed);
		free(new->name);
		free(new);
		return (E_SUCCESS);
	}
	else if (list->end)
	{
		list->end->next = new;
		new->prev = list->end;
	}
	else
		list->start = new;
	list->list_len++;
	list->end = new;
	return (list_calc(list, new));
}
