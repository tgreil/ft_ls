/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_o.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 17:52:09 by tgreil            #+#    #+#             */
/*   Updated: 2018/04/27 16:32:30 by tgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_printf_oo(t_printf *pf)
{
	if (pf->conv.size < 5)
		pf->conv.size = 5;
	ft_printf_o(pf);
	return (EXIT_SUCCESS);
}

int			ft_printf_o(t_printf *pf)
{
	unsigned long long	nbr;
	char				*c_nbr;

	pf->conv.space_it = FALSE;
	nbr = ft_printf_type_get(pf, pf->conv.size, 1);
	if (!(c_nbr = ft_llong_itoa(nbr, "01234567")))
		return (EXIT_ERROR);
	ft_printf_field_calc(pf, nbr, c_nbr, NULL);
	if (pf->conv.chang && nbr)
	{
		if (pf->conv.precision <= 0)
			pf->conv.precision = 1;
		pf->conv.field_min--;
	}
	ft_printf_field_print(pf, LEFT);
	pf->printed += ft_print_char_xtime('0', pf->conv.precision, pf->fd);
	if (nbr || !pf->conv.to_precis || !pf->conv.precision || pf->conv.chang)
		pf->printed += ft_putstr_fd(c_nbr, pf->fd);
	else if (pf->conv.field_min > 0)
		pf->printed += ft_putstr_fd(" ", pf->fd);
	ft_printf_field_print(pf, RIGHT);
	free(c_nbr);
	return (EXIT_SUCCESS);
}
