/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_manag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 10:24:11 by tgreil            #+#    #+#             */
/*   Updated: 2018/06/29 20:18:43 by tgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		list_sort(t_list_manag *list, int sens,
									int (*f)(t_list_ls *, t_list_ls *))
{
	t_list_ls	*last;

	last = NULL;
	list->act = list->start;
	while (list->act && list->act->next)
	{
		if ((!sens && f(list->act, list->act->next) > 0) ||
			(sens && f(list->act, list->act->next) < 0))
		{
			if (!last)
				list->start = list->act->next;
			else
				last->next = list->act->next;
			last = list->act->next->next;
			list->act->next->next = list->act;
			list->act->next = last;
			last = NULL;
			list->act = list->start;
		}
		else
		{
			last = list->act;
			list->act = list->act->next;
		}
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
	new->folder.list_len = 0;
	new->folder.path = NULL;
	new->folder.start = NULL;
	new->folder.act = NULL;
	new->list = list;
	return (new);
}

int			list_calc(t_list_manag *list, t_list_ls *new)
{
	list->calc[0] += new->stat.st_blocks;
	if (list->calc[1] < int_get_unit(new->stat.st_nlink))
		list->calc[1] = int_get_unit(new->stat.st_nlink);
	if (list->calc[2] < (int)ft_strlen(new->passwd->pw_name))
		list->calc[2] = (int)ft_strlen(new->passwd->pw_name);
	if (list->calc[3] < (int)ft_strlen(new->group->gr_name))
		list->calc[3] = (int)ft_strlen(new->group->gr_name);
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
	new->next = list->start;
	list->start = new;
	list->list_len++;
	new->passwd = getpwuid(new->stat.st_uid);
	new->group = getgrgid(new->stat.st_gid);
	return (list_calc(list, new));
}
