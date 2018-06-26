/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_apply.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 12:50:17 by tgreil            #+#    #+#             */
/*   Updated: 2018/06/26 19:16:01 by tgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_ls_apply_unit(t_container *c, t_list_ls *elem)
{
	if ((elem->stat.st_mode & S_IFDIR))
	{
		if (!(elem->dir_dir = opendir(elem->name)))
			return (E_SUCCESS); // MSG FAIL OPEN DIR
		while ((elem->dirent = readdir(elem->dir_dir)))
		{
			if (elem->dirent->d_name[0] != '.' ||
				option_is_set(c->option, OPTION_A))
			{
				if (list_add(&elem->folder, ft_strdup(elem->dirent->d_name)) < 0)
					return (E_ERROR);
				ft_printf("%s\n", elem->folder.end->name);
			}
		}
		closedir(elem->dir_dir);
	}
	return (E_SUCCESS);
}

int		ft_ls_apply(t_container *c, t_list_manag *list, int level)
{
	list->act = list->start;
	while (list->act)
	{
		if (ft_ls_apply_unit(c, list->act) == E_ERROR)
			return (E_ERROR);
		if (list->act->state > 0 && (list->act->stat.st_mode & S_IFDIR) &&
			list->act->folder.list_len &&
			(!level || option_is_set(c->option, OPTION_RR)) &&
			(!level || (ft_strcmp(list->act->name, ".") && ft_strcmp(list->act->name, ".."))))
			ls_function(c, &list->act->folder, level + 1);
		list->act = list->act->next;
	}
	return (E_SUCCESS);
}
