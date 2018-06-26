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

int		ft_ls_apply_f(t_list_manag *list, t_list_ls *elem, unsigned int option)
{
	if ((elem->stat.st_mode & S_IFDIR))
	{
		if (!(elem->dir_dir = opendir(elem->name)))
			return (E_SUCCESS); // MSG FAIL OPEN DIR
		while ((elem->dirent = readdir(elem->dir_dir)))
		{
			if (elem->dirent->d_name[0] != '.' ||
				option_is_set(option, OPTION_A))
			{
				if (list_add(&elem->folder, ft_strdup(elem->dirent->d_name)) < 0)
					return (E_ERROR);
				elem->folder.list_len++;
			}
		}
		closedir(elem->dir_dir);
	}
	list += 1;
	return (E_SUCCESS);
}

int		ft_ls_apply(t_container *c, t_list_manag *list, int level)
{
	if (!level || option_is_set(c->option, OPTION_RR))
		list_apply(list, &ft_ls_apply_f, c->option);
	return (E_SUCCESS);
}
