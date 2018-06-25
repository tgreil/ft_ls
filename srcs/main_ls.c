/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ls.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 12:26:19 by tgreil            #+#    #+#             */
/*   Updated: 2018/06/25 11:36:20 by tgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ls_initializer(t_container *c)
{
	c->option = 0;
	c->list_name.end = NULL;
	c->list_name.start = NULL;
	c->list_name.list_len = 0;
}

int			ls_exit(t_container *c, int status)
{
	while (c->list_name.start)
	{
		c->list_name.start = c->list_name.start->next;
		if (c->list_name.start)
			free(c->list_name.start->prev);
	}
	free(c->list_name.end);
	return (status);
}

int			main(int ac, char **av)
{
	t_container	c;

	ls_initializer(&c);
	if (param_handler(&c, ac, av) == E_ERROR)
		return (E_ERROR);
	return (E_SUCCESS);
}
