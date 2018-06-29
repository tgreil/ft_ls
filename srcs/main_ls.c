/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ls.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 12:26:19 by tgreil            #+#    #+#             */
/*   Updated: 2018/06/29 20:20:29 by tgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ls_initializer(t_container *c)
{
	ft_bzero(c, sizeof(t_container));
	c->option = 0;
	c->list_param.start = NULL;
	c->list_param.list_len = 0;
	c->list_param.path = NULL;
}

int			ls_function(t_container *c, t_list_manag *list)
{
	if (ft_ls_apply(c, list) == E_ERROR)
		return (E_ERROR);
	list_sort(list, option_is_set(c->option, OPTION_R), &sort_name);
	if (option_is_set(c->option, OPTION_T))
		list_sort(list, option_is_set(c->option, OPTION_R), &sort_date);
	print_result(c, list);
	return (E_SUCCESS);
}

int			main(int ac, char **av)
{
	t_container	c;

	ls_initializer(&c);
	if (param_handler(&c, ac, av) == E_ERROR)
		return (E_ERROR);
	if (c.list_param.list_len <= 0)
		list_add(&c.list_param, ft_strdup("."));
	c.list_param.level = 0;
	if (ls_function(&c, &c.list_param) == E_ERROR)
		return (E_ERROR);
	return (E_SUCCESS);
}
