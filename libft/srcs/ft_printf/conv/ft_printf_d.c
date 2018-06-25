/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 15:32:36 by tgreil            #+#    #+#             */
/*   Updated: 2018/04/27 16:32:24 by tgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_printf_dd(t_printf *pf)
{
	if (pf->conv.size < 5)
		pf->conv.size = 5;
	ft_printf_d(pf);
	return (EXIT_SUCCESS);
}

int		ft_printf_d(t_printf *pf)
{
	long long	nbr;
	char		*c_nbr;

	nbr = ft_printf_type_get(pf, pf->conv.size, 0);
	if (nbr < 0 || pf->conv.to_sign)
		pf->conv.space_it = FALSE;
	if (!(c_nbr = ft_llong_itoa(nbr < 0 ? -nbr : nbr, "0123456789")))
		return (EXIT_ERROR);
	ft_printf_field_calc(pf, nbr, c_nbr, NULL);
	ft_printf_field_print(pf, LEFT);
	ft_printf_sign_print(pf, nbr < 0);
	pf->printed += ft_print_char_xtime('0', pf->conv.precision, pf->fd);
	if (nbr || !pf->conv.to_precis ||
								pf->conv.precision >= (int)ft_strlen(c_nbr))
		pf->printed += ft_putstr_fd(c_nbr, pf->fd);
	else if (pf->conv.field_min > 0)
		pf->printed += ft_putstr_fd(" ", pf->fd);
	ft_printf_field_print(pf, RIGHT);
	free(c_nbr);
	return (EXIT_SUCCESS);
}

int		ft_printf_i(t_printf *pf)
{
	return (ft_printf_d(pf));
}
