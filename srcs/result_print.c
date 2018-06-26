/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   result_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 11:57:43 by tgreil            #+#    #+#             */
/*   Updated: 2018/06/26 19:31:51 by tgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		result_print_unit_time(t_list_ls *elem)
{
	elem += 1; // a changer
	ft_printf("Jun 25 12:49 ");
	return (E_SUCCESS);
}

int		result_print_unit_rights(t_list_ls *elem)
{
	ft_printf("%c", (elem->stat.st_mode & S_IFDIR) ? 'd' : '-');
	ft_printf("%c", (elem->stat.st_mode & S_IRUSR) ? 'r' : '-');
	ft_printf("%c", (elem->stat.st_mode & S_IWUSR) ? 'w' : '-');
	ft_printf("%c", (elem->stat.st_mode & S_IXUSR) ? 'x' : '-');
	ft_printf("%c", (elem->stat.st_mode & S_IRGRP) ? 'r' : '-');
	ft_printf("%c", (elem->stat.st_mode & S_IWGRP) ? 'w' : '-');
	ft_printf("%c", (elem->stat.st_mode & S_IXGRP) ? 'x' : '-');
	ft_printf("%c", (elem->stat.st_mode & S_IROTH) ? 'r' : '-');
	ft_printf("%c", (elem->stat.st_mode & S_IWOTH) ? 'w' : '-');
	ft_printf("%c  ", (elem->stat.st_mode & S_IWOTH) ? 'x' : '-');
	return (E_SUCCESS);
}

int		result_print_unit(t_container *c, t_list_ls *elem)
{
	if (option_is_set(c->option, OPTION_L))
	{
		result_print_unit_rights(elem);
		ft_printf("%*d ", 2, 7); // a changer
		ft_printf("%s  ", "tgreil"); // a changer
		ft_printf("%s  ", "2018_paris"); // a changer
		ft_printf("%*d ", 5, 4242);// a changer
		result_print_unit_time(elem);
	}
	if ((elem->stat.st_mode & S_IFDIR))
		ft_printf("{light blue}");
	ft_printf("%s\n", elem->name);
	ft_printf("{eoc}");
	return (E_SUCCESS);
}

int		result_print(t_container *c, t_list_manag *list, int level)
{
	list->act = list->start;
	while (list->act)
	{
		// calculer les len max
		list->act = list->act->next;
	}
	list->act = list->start;
	while (list->act)
	{
		if (list->act->folder.list_len > 0 &&
			(!level || option_is_set(c->option, OPTION_RR)))
		{
			if (list->act->prev)
				ft_printf("\n");
			if (list->list_len > 1)
				ft_printf("%s:\n", list->act->name);
			if (ls_function(c, &list->act->folder, level + 1) == E_ERROR)
				return (E_ERROR);
		}
		else
			result_print_unit(c, list->act);
		list->act = list->act->next;
	}
	return (E_SUCCESS);
}
