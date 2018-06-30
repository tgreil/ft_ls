/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_apply.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 12:50:17 by tgreil            #+#    #+#             */
/*   Updated: 2018/06/30 19:23:55 by tgreil           ###   ########.fr       */
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
	if (S_ISDIR(elem->stat.st_mode) &&
		(!elem->list->level || option_is_set(c->option, OPTION_RR)))
	{
		path_maker(elem);
		elem->folder.from = elem;
		if (!(elem->dir_dir = opendir(elem->name_pathed)))
		{
			elem->state = -2;
			return (E_SUCCESS);
		}
		while ((elem->dirent = readdir(elem->dir_dir)))
		{
			if (elem->dirent->d_name[0] != '.' ||
				option_is_set(c->option, OPTION_A))
			{
				if (list_add(&elem->folder, elem->dirent->d_name) < 0)
					return (E_ERROR);
			}
		}
		closedir(elem->dir_dir);
	}
	return (E_SUCCESS);
}

int		ft_ls_apply(t_container *c, t_list_manag *list)
{
	list->act = list->start;
	while (list->act)
	{
		if (ft_ls_apply_unit(c, list->act) == E_ERROR)
			return (E_ERROR);
		list->act->folder.level = list->level + 1;
		list->act = list->act->next;
	}
	return (E_SUCCESS);
}
