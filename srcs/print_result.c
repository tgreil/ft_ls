/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_result.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 11:57:43 by tgreil            #+#    #+#             */
/*   Updated: 2018/06/28 17:22:31 by tgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		print_rights(t_list_ls *elem)
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
	ft_printf("%c ", (elem->stat.st_mode & S_IXOTH) ? 'x' : '-');
	return (E_SUCCESS);
}

int		print_number(t_list_ls *elem)
{
	ft_printf("%*d ", elem->list->calc[1] + 1, elem->stat.st_nlink);
	return (E_SUCCESS);
}

int		print_user(t_list_ls *elem)
{
	ft_printf("%*s ", elem->list->calc[2], "tgreil"); // a changer
	return (E_SUCCESS);
}

int		print_groupe(t_list_ls *elem)
{
	ft_printf("%*s ", elem->list->calc[3] + 1, "2018_paris"); // a changer
	return (E_SUCCESS);
}

int		print_size(t_list_ls *elem)
{
	ft_printf("%*d ", elem->list->calc[4] + 1, elem->stat.st_size);
	return (E_SUCCESS);
}

int		print_time(t_list_ls *elem)
{
	char	*date;

	date = ctime(&elem->stat.st_mtime);
	date[ft_strlen(date) - 4] = ' ';
	date[ft_strlen(date) - 5] = '\0';
	date += 4;
	ft_printf("%s", date);
	return (E_SUCCESS);
}

int		print_option_l(t_list_ls *elem)
{
	print_rights(elem);
	print_number(elem);
	print_user(elem);
	print_groupe(elem);
	print_size(elem);
	print_time(elem);
	return (E_SUCCESS);
}

int		print_name(t_list_ls *elem, int to_color)
{
	if (to_color)
	{
		if ((elem->stat.st_mode & S_IFDIR))
			ft_printf("{light blue}");
		else if ((elem->stat.st_mode & S_IXUSR))
			ft_printf("{light red}");
	}
	ft_printf("%s\n", elem->name);
	if (to_color)
		ft_printf("{eoc}");
	return (E_SUCCESS);
}

int		print_result_unit(t_container *c, t_list_ls *elem)
{

	if (option_is_set(c->option, OPTION_L))
		print_option_l(elem);
	print_name(elem, option_is_set(c->option, OPTION_C));
	return (E_SUCCESS);
}

int		print_result(t_container *c, t_list_manag *list, int level)
{
	list->act = list->start;
	// bzero list->calc
	while (list->act)
	{
		if ((list->act->stat.st_mode & S_IFDIR) &&
			(!level || option_is_set(c->option, OPTION_RR)))
		{
			if (list->act && list->act->prev)
				ft_printf("\n");
			if (list->list_len > 1)
				ft_printf("%s:\n", list->act->name_pathed);
			if (option_is_set(c->option, OPTION_L))
				ft_printf("total %d\n", list->act->folder.calc[0]);
			print_result(c, &list->act->folder, level + 1);
		}
		else
			print_result_unit(c, list->act);
		list->act = list->act->next;
	}
	return (E_SUCCESS);
}
