/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_manag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 10:24:11 by tgreil            #+#    #+#             */
/*   Updated: 2018/06/30 16:32:46 by tgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		list_swap(t_list_manag *list, t_list_ls *prev, t_list_ls *act)
{
	prev->next = act->next;
	if (act->next)
		act->next->prev = prev;
	act->next = prev;
	act->prev = prev->prev;
	if (act->prev)
		prev->prev->next = act;
	else
		list->start = act;
	prev->prev = act;
}

void		list_sort(t_list_manag *list, int sens,
									int (*f)(t_list_ls *, t_list_ls *))
{
	t_list_ls	*prev;
	t_list_ls	*act;

	prev = NULL;
	act = list->start;
	while (act)
	{
		while (act && prev &&
				((!sens && f(prev, act) > 0) ||
				(sens && f(prev, act) < 0)))
		{
			list_swap(list, prev, act);
			prev = act->prev;
		}
		prev = act;
		act = act->next;
	}
}

t_list_ls	*list_create(t_list_manag *list, char *name)
{
	t_list_ls	*new;

	if (!(new = malloc(sizeof(t_list_ls))))
		return (NULL);
	ft_bzero(new, sizeof(t_list_ls));
	new->next = NULL;
	if (!(new->name = ft_strdup(name)))
		return (NULL);
	if (list->path)
		new->name_pathed = ft_strjoin(list->path, name);
	else
		new->name_pathed = ft_strdup(name);
	new->state = lstat(new->name_pathed, &new->stat);
	new->list = list;
	return (new);
}

int			list_calc(t_list_manag *list, t_list_ls *new)
{
	list->calc[0] += new->stat.st_blocks;
	if (list->calc[1] < int_get_unit(new->stat.st_nlink))
		list->calc[1] = int_get_unit(new->stat.st_nlink);
	if (new->passwd && list->calc[2] < (int)ft_strlen(new->passwd->pw_name))
		list->calc[2] = (int)ft_strlen(new->passwd->pw_name);
	else if (list->calc[2] < int_get_unit(new->stat.st_uid))
		list->calc[2] = int_get_unit(new->stat.st_uid);
	if (new->group && list->calc[3] < (int)ft_strlen(new->group->gr_name))
		list->calc[3] = (int)ft_strlen(new->group->gr_name);
	else if (list->calc[3] < int_get_unit(new->stat.st_gid))
		list->calc[3] = int_get_unit(new->stat.st_gid);
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
		// stock msg
		free(new->name_pathed);
		free(new->name);
		free(new);
		return (E_SUCCESS);
	}
	if ((new->next = list->start))
		list->start->prev = new;
	list->start = new;
	list->list_len++;
	new->passwd = getpwuid(new->stat.st_uid);
	new->group = getgrgid(new->stat.st_gid);
	return (list_calc(list, new));
}
