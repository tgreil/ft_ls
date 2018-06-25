/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   result_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 11:57:43 by tgreil            #+#    #+#             */
/*   Updated: 2018/06/25 18:00:02 by tgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
	ft_printf("%c ", (elem->stat.st_mode & S_IWOTH) ? 'x' : '-');
	return (E_SUCCESS);
}

int		result_print_unit(t_container *c, t_list_ls *elem)
{
	if (option_is_set(c->option, OPTION_L))
		result_print_unit_rights(elem);
	if ((elem->stat.st_mode & S_IFDIR))
		ft_printf("{light blue}");
	ft_printf("%s\n", elem->name);
	ft_printf("{eoc}");
	return (E_SUCCESS);
}

int		result_print(t_container *c)
{
	c->list_name.act = c->list_name.start;
	while (c->list_name.act)
	{
		if (c->list_name.act->name[0] != '.' ||
									option_is_set(c->option, OPTION_A))
			result_print_unit(c, c->list_name.act);
		c->list_name.act = c->list_name.act->next;
	}
	return (E_SUCCESS);
}
