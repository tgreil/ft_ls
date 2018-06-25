/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 18:11:42 by tgreil            #+#    #+#             */
/*   Updated: 2018/04/27 16:32:38 by tgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_printf_uu(t_printf *pf)
{
	if (pf->conv.size < 5)
		pf->conv.size = 5;
	ft_printf_u(pf);
	return (EXIT_SUCCESS);
}

int			ft_printf_u(t_printf *pf)
{
	unsigned long long	nbr;
	char				*c_nbr;

	pf->conv.to_sign = FALSE;
	pf->conv.space_it = FALSE;
	nbr = ft_printf_type_get(pf, pf->conv.size, 1);
	if (!(c_nbr = ft_llong_itoa(nbr, "0123456789")))
		return (EXIT_ERROR);
	ft_printf_field_calc(pf, nbr, c_nbr, NULL);
	ft_printf_field_print(pf, LEFT);
	pf->printed += ft_print_char_xtime('0', pf->conv.precision, pf->fd);
	if (nbr || !pf->conv.to_precis || !pf->conv.precision)
		pf->printed += ft_putstr_fd(c_nbr, pf->fd);
	else if (pf->conv.field_min > 0)
		pf->printed += ft_putstr_fd(" ", pf->fd);
	ft_printf_field_print(pf, RIGHT);
	free(c_nbr);
	return (EXIT_SUCCESS);
}
