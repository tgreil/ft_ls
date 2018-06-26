/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 19:28:32 by tgreil            #+#    #+#             */
/*   Updated: 2018/06/26 19:37:33 by tgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"


int			sort_date(t_list_ls *one, t_list_ls *two)
{
 	if (one->stat.st_ctime >= two->stat.st_ctime)
		return (-1);
	return (1);
}

int			sort_name(t_list_ls *one, t_list_ls *two)
{
	return (ft_strcmp(one->name, two->name));
}
