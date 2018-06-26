/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ls.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 12:26:19 by tgreil            #+#    #+#             */
/*   Updated: 2018/06/26 09:36:30 by tgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ls_initializer(t_container *c)
{
	c->option = 0;
	c->list_param.end = NULL;
	c->list_param.start = NULL;
	c->list_param.list_len = 0;
}

int			ls_exit(t_container *c, int status)
{
	while (c->list_param.start)
	{
		c->list_param.start = c->list_param.start->next;
		if (c->list_param.start)
		{
			if (c->list_param.start->name_malloced == TRUE)
				free(c->list_param.start->name);
			free(c->list_param.start->prev);
		}
	}
	if (c->list_param.end->name_malloced == TRUE)
		free(c->list_param.end->name);
	free(c->list_param.end);
	return (status);
}

int			main(int ac, char **av)
{
	t_container	c;

	ls_initializer(&c);
	if (param_handler(&c, ac, av) == E_ERROR)
		return (E_ERROR);
	if (c.list_param.list_len <= 0)
	{
		list_add(&c.list_param, ft_strdup("."));
		c.list_param.end->name_malloced = TRUE;
	}
	if (ft_ls_apply(&c) == E_ERROR)
		return (E_ERROR);
	list_sort(&c.list_param, option_is_set(c.option, OPTION_R));
	result_print(&c);
	return (E_SUCCESS);
}
