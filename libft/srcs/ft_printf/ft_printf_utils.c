/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 15:32:55 by tgreil            #+#    #+#             */
/*   Updated: 2018/04/27 16:30:36 by tgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_printf_field_calc(t_printf *pf, long long nbr, char *c_nbr,
																	char *pre)
{
	int	c_nbr_len;

	c_nbr_len = ft_strlen(c_nbr);
	pf->conv.precision -= c_nbr_len;
	if (pf->conv.chang && pre)
		c_nbr_len += ft_strlen(pre);
	if (pf->conv.to_sign || nbr < 0 || (!c_nbr_len && pf->conv.space_it))
		c_nbr_len++;
	pf->conv.field_min -= c_nbr_len;
	if (pf->conv.precision > 0)
	{
		pf->conv.field_min -= pf->conv.precision;
		pf->conv.field_fill_char = ' ';
	}
	if (pf->conv.field_min < 0 && pf->conv.space_it &&
												!pf->conv.to_sign && nbr >= 0)
		pf->conv.field_min = 1;
	if (pf->conv.field_fill_char != ' ' && pf->conv.precision < 0 &&
											pf->conv.field_fill_side != RIGHT)
	{
		if (pf->conv.space_it)
			pf->conv.field_fill_char = ' ';
		pf->conv.precision = pf->conv.field_min - (pf->conv.space_it ? 1 : 0);
		pf->conv.field_min = pf->conv.space_it ? 1 : 0;
	}
}

void		ft_printf_sign_print(t_printf *pf, char is_neg)
{
	if (is_neg || pf->conv.to_sign)
	{
		if (is_neg)
			pf->printed += ft_putchar_fd('-', pf->fd);
		else
			pf->printed += ft_putchar_fd('+', pf->fd);
	}
}

void		ft_printf_field_print(t_printf *pf, char s)
{
	char	c;

	c = pf->conv.field_fill_char;
	if (s == pf->conv.field_fill_side)
	{
		if (s == RIGHT)
			c = ' ';
		pf->printed += ft_print_char_xtime(c, pf->conv.field_min, pf->fd);
	}
}

long long	ft_printf_type_get2(t_printf *pf, char type)
{
	long long	nbr;

	if (type == 1)
		nbr = (unsigned short)va_arg(pf->ap, unsigned int);
	else if (type == 2)
		nbr = (unsigned char)va_arg(pf->ap, unsigned int);
	else if (type == 5 || type == 3)
		nbr = va_arg(pf->ap, unsigned long);
	else if (type == 6 || type == 4)
		nbr = va_arg(pf->ap, unsigned long long);
	else
		nbr = va_arg(pf->ap, unsigned int);
	return (nbr);
}

long long	ft_printf_type_get(t_printf *pf, char type, char unsign)
{
	long long	nbr;

	if (unsign)
		return (ft_printf_type_get2(pf, type));
	if (type == 1)
		nbr = (short)va_arg(pf->ap, int);
	else if (type == 2)
		nbr = (char)va_arg(pf->ap, int);
	else if (type == 5 || type == 3)
		nbr = va_arg(pf->ap, long);
	else if (type == 6 || type == 4)
		nbr = va_arg(pf->ap, long long);
	else
		nbr = va_arg(pf->ap, int);
	return (nbr);
}
