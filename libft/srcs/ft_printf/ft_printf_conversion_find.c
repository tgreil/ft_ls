/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conversion_find.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 15:32:28 by tgreil            #+#    #+#             */
/*   Updated: 2018/04/27 16:32:00 by tgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_printf_conversion_default(t_printf *pf, char conv_c)
{
	char	c[2];

	c[0] = conv_c;
	c[1] = '\0';
	pf->conv.space_it = FALSE;
	ft_printf_field_calc(pf, 1, c, NULL);
	ft_printf_field_print(pf, LEFT);
	pf->printed += ft_print_char_xtime('0', pf->conv.precision, pf->fd);
	pf->printed += ft_putstr_fd(c, pf->fd);
	ft_printf_field_print(pf, RIGHT);
	return (EXIT_SUCCESS);
}

int		ft_printf_conversion_find2(t_printf *pf, char conv_c)
{
	if (conv_c == 'n')
		return (ft_printf_n(pf));
	else if (conv_c == 'o')
		return (ft_printf_o(pf));
	else if (conv_c == 'O')
		return (ft_printf_oo(pf));
	else if (conv_c == 'p')
		return (ft_printf_p(pf));
	else if (conv_c == 's')
		return (ft_printf_s(pf));
	else if (conv_c == 'S')
		return (ft_printf_ss(pf));
	else if (conv_c == 'u')
		return (ft_printf_u(pf));
	else if (conv_c == 'U')
		return (ft_printf_uu(pf));
	else if (conv_c == 'x')
		return (ft_printf_x(pf));
	else if (conv_c == 'X')
		return (ft_printf_xx(pf));
	else if (conv_c == '%')
		return (ft_printf_mod(pf));
	return (ft_printf_conversion_default(pf, conv_c));
}

int		ft_printf_conversion_find(t_printf *pf, char conv_c)
{
	if (conv_c == 'b')
		return (ft_printf_b(pf));
	else if (conv_c == 'c')
		return (ft_printf_c(pf));
	else if (conv_c == 'C')
		return (ft_printf_cc(pf));
	else if (conv_c == 'd' || conv_c == 'i')
		return (ft_printf_d(pf));
	else if (conv_c == 'D')
		return (ft_printf_dd(pf));
	return (ft_printf_conversion_find2(pf, conv_c));
}
