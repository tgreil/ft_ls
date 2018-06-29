/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_apply.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 12:50:17 by tgreil            #+#    #+#             */
/*   Updated: 2018/06/29 14:01:44 by tgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		path_maker(t_list_ls *elem)
{
	char	*new;

	new = NULL;
	if (elem->list->path)
		new = ft_strjoin(elem->list->path, elem->name);
	else
		new = ft_strdup(elem->name);
	if (new)
		elem->folder.path = ft_strjoin(new, "/");
	else
		elem->folder.path = NULL;
	if (new)
		free(new);
	return (E_SUCCESS);
}

int		ft_ls_apply_unit(t_container *c, t_list_ls *elem)
{
	if ((elem->stat.st_mode & S_IFDIR) &&
		(!elem->list->level || option_is_set(c->option, OPTION_RR)))
	{

		if (!(elem->dir_dir = opendir(elem->name_pathed)))
			return (E_SUCCESS  + 0 * ft_printf("{cyan}%s{eoc}\n", elem->name_pathed)); // MSG FAIL OPEN DIR
		while ((elem->dirent = readdir(elem->dir_dir)))
		{
			if (elem->dirent->d_name[0] != '.' ||
				option_is_set(c->option, OPTION_A))
			{
				if (!elem->folder.list_len)
					path_maker(elem);
				if (list_add(&elem->folder, elem->dirent->d_name) < 0)
					return (E_ERROR);
				elem->folder.from = elem;
			}
		}
		closedir(elem->dir_dir);
	}
	return (E_SUCCESS);
}

int		ft_ls_apply(t_container *c, t_list_manag *list)
{
	t_list_manag	*tmp;

	list->act = list->start;
	while (list->act)
	{
		if (ft_ls_apply_unit(c, list->act) == E_ERROR)
			return (E_ERROR);
		if (list->act->folder.list_len > 0 &&
			(!list->level || (ft_strcmp(list->act->name, ".") &&
											ft_strcmp(list->act->name, ".."))))
		{
			tmp = list;
			while (tmp && tmp->next && tmp->next->level <= list->level + 1)
				tmp = tmp->next;
			list->act->folder.level = list->level + 1;
			list->act->folder.next = tmp->next;
			tmp->next = &list->act->folder;
			// add to stack
		}
		list->act = list->act->next;
	}
	return (E_SUCCESS);
}
