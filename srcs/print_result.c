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

int		print_time(t_list_ls *elem, int flag)
{
	if (flag)
	{
		elem += 1; // a changer
		ft_printf("Jun 25 12:49 ");
	}
	return (E_SUCCESS);
}

int		print_rights(t_list_ls *elem, int flag)
{
	if (flag)
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
		ft_printf("%c ", (elem->stat.st_mode & S_IWOTH) ? 'x' : '-');
	}
	return (E_SUCCESS);
}

int		print_size(t_list_ls *elem, int flag)
{
	if (flag)
		ft_printf("%*d ", 5, elem->stat.st_size);// a changer
	else if (elem->list->calc[0] < elem->stat.st_size)
		elem->list->calc[0] = elem->stat.st_size;
	return (E_SUCCESS);
}

int		print_option_l(t_list_ls *elem, int flag)
{
	print_rights(elem, flag);
	if (flag)
	{ // a delete, chacun son if
		ft_printf("%*d ", 2, 7); // a changer
		ft_printf("%s ", "tgreil"); // a changer
		ft_printf("%s ", "2018_paris"); // a changer
	}
	print_size(elem, flag);
	print_time(elem, flag);
	return (E_SUCCESS);
}

int		print_name(t_list_ls *elem, int flag)
{
	if (flag)
	{
		if ((elem->stat.st_mode & S_IFDIR))
			ft_printf("{light blue}");
		ft_printf("%s\n", elem->name);
		ft_printf("{eoc}");
	}
	return (E_SUCCESS);
}

int		print_result_unit(t_container *c, t_list_ls *elem, int flag)
{
	if (option_is_set(c->option, OPTION_L))
		print_option_l(elem, flag);
	print_name(elem, flag);
	if (flag <= 0)
		print_result_unit(c, elem, flag + 1);
	return (E_SUCCESS);
}

int		print_result(t_container *c, t_list_manag *list, int level)
{
	ft_printf("list_len: %d\n", list->list_len);
	list->act = list->start;
	// bzero list->calc
	while (list->act)
	{
		if (list->act->folder.list_len > 0 &&
			(!level || option_is_set(c->option, OPTION_RR)))
		{
			if (list->act->prev)
				ft_printf("\n");
			if (list->list_len > 1)
				ft_printf("%s:\n", list->act->name);
			print_result(c, &list->act->folder, level + 1);
			// recursif dans dossier ( elem->list->folder )
		}
		else
			print_result_unit(c, list->act, 0);
		list->act = list->act->next;
	}
	return (E_SUCCESS);
}
