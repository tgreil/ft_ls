/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_apply.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 12:50:17 by tgreil            #+#    #+#             */
/*   Updated: 2018/06/25 12:59:54 by tgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_ls_apply_f(t_list_manag *list, t_list_ls *elem)
{
	if (elem->stat.st_mode & S_IFDIR)
	{
		ft_printf("DIR\n");
	}
	list += 1;
	return (E_SUCCESS);
}

int		ft_ls_apply(t_container *c)
{
	list_apply(&c->list_name, &ft_ls_apply_f);
	return (E_SUCCESS);
}
