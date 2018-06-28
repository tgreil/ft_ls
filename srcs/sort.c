/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 19:28:32 by tgreil            #+#    #+#             */
/*   Updated: 2018/06/27 16:16:30 by tgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"


int			sort_date(t_list_ls *one, t_list_ls *two)
{
	if (one->stat.st_mtime == two->stat.st_mtime)
		return (0);
 	else if (one->stat.st_mtime > two->stat.st_mtime)
		return (-1);
	return (1);
}

int			sort_name(t_list_ls *one, t_list_ls *two)
{
	return (ft_strcmp(one->name, two->name));
}
