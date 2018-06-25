/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_x.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 15:28:14 by tgreil            #+#    #+#             */
/*   Updated: 2018/04/27 16:32:40 by tgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_printf_xxx(t_printf *pf, char *base, char *prefix, int p)
{
	unsigned long long	nbr;
	char				*c_nbr;

	pf->conv.space_it = FALSE;
	nbr = ft_printf_type_get(pf, pf->conv.size, 1);
	if (!(c_nbr = ft_llong_itoa(nbr, base)))
		return (EXIT_ERROR);
	if (!p)
		ft_printf_field_calc(pf, nbr, c_nbr, nbr ? prefix : NULL);
	else
		ft_printf_field_calc(pf, nbr, c_nbr, prefix);
	ft_printf_field_print(pf, LEFT);
	if ((pf->conv.chang && nbr) || p)
		pf->printed += ft_putstr_fd(prefix, pf->fd);
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

int			ft_printf_xx(t_printf *pf)
{
	return (ft_printf_xxx(pf, "0123456789ABCDEF", "0X", 0));
}

int			ft_printf_x(t_printf *pf)
{
	return (ft_printf_xxx(pf, "0123456789abcdef", "0x", 0));
}
