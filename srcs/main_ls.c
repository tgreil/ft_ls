/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ls.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 12:26:19 by tgreil            #+#    #+#             */
/*   Updated: 2018/06/30 19:19:12 by tgreil           ###   ########.fr       */
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

int			ls_function_rec(t_container *c, t_list_manag *list)
{
	list->act = list->start;
	while (list->act)
	{
		if (list->act->state == -2)
		{
			if (list->level > 0 || list->act->prev)
				ft_printf("\n");
			ft_printf("%s:\n", list->act->name_pathed);
			ft_printf("!2!%s%s: Permission denied\n",
											LS_ERROR_MSG, list->act->name);
		}
		else if (S_ISDIR(list->act->stat.st_mode) &&
				(option_is_set(c->option, OPTION_RR) || !list->level) &&
			(!list->level || (ft_strcmp(list->act->name, ".") &&
											ft_strcmp(list->act->name, ".."))))
			ls_function(c, &list->act->folder);
		list->act = list->act->next;
	}
	return (E_SUCCESS);
}

int			ls_function(t_container *c, t_list_manag *list)
{
	if (ft_ls_apply(c, list) == E_ERROR)
		return (E_ERROR);
	list_sort(list, option_is_set(c->option, OPTION_R), &sort_name);
	if (option_is_set(c->option, OPTION_T))
		list_sort(list, option_is_set(c->option, OPTION_R), &sort_date);
	print_result(c, list);
	if (list->level && list->list_len == 0 &&
							(list->from || c->list_param.list_len > 1))
	{
		if (&c->list_param.start->folder != list)
			ft_printf("\n");
		ft_printf("%s:\n", list->name);
	}
	ls_function_rec(c, list);
	return (E_SUCCESS);
}

int			ls_exit(t_list_manag *list, int status)
{
	t_list_ls	*last;

	list->act = list->start;
	while (list->act)
	{
		last = list->act;
		if (list->act->folder.list_len > 0)
			ls_exit(&list->act->folder, status);
		free(last->name);
		free(last->name_pathed);
		free(last->folder.path);
		list->act = list->act->next;
		free(last);
	}
	return (status);
}

int			main(int ac, char **av)
{
	t_container	c;

	ls_initializer(&c);
	if (param_handler(&c, ac, av) == E_ERROR)
		return (E_ERROR);
	c.list_param.level = 0;
	if (ls_function(&c, &c.list_param) == E_ERROR)
		return (E_ERROR);
	return (ls_exit(&c.list_param, E_SUCCESS));
}
