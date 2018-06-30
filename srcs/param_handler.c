/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 10:37:55 by tgreil            #+#    #+#             */
/*   Updated: 2018/06/30 15:26:59 by tgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		param_handler_option(t_container *c, char *string)
{
	size_t	i;

	i = 1;
	while (string[i])
	{
		if (string[i] == OPTION_L_C)
			option_set(&c->option, OPTION_L);
		else if (string[i] == OPTION_RR_C)
			option_set(&c->option, OPTION_RR);
		else if (string[i] == OPTION_A_C)
			option_set(&c->option, OPTION_A);
		else if (string[i] == OPTION_R_C)
			option_set(&c->option, OPTION_R);
		else if (string[i] == OPTION_T_C)
			option_set(&c->option, OPTION_T);
		else if (string[i] == OPTION_C_C)
			option_set(&c->option, OPTION_C);
		else if (string[i] == '-')
			return (E_ERROR);
		else
			ft_printf("!2!%sInvalid option \"%c\"\n", LS_ERROR_MSG, string[i]);
		i++;
	}
	return (E_SUCCESS);
}

int		param_handler_file(t_container *c, char *name)
{
	if (list_add(&c->list_param, name) == E_ERROR)
		return (E_ERROR);
	return (E_SUCCESS);
}

int		param_handler(t_container *c, int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac && av[i][0] == '-')
	{
		if (param_handler_option(c, av[i++]) == E_ERROR)
			break ;
	}
	if (i >= ac)
		list_add(&c->list_param, ".");
	while (i < ac)
	{
		if (param_handler_file(c, av[i]) == E_ERROR)
			return (E_ERROR);
		i++;
	}
	return (E_SUCCESS);
}
