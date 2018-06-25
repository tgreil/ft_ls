/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 15:32:15 by tgreil            #+#    #+#             */
/*   Updated: 2018/04/27 16:20:42 by tgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_putwchar_fd(unsigned int wc, int fd)
{
	int	printed;

	printed = 0;
	if (wc <= 127)
		printed += ft_putchar_fd(wc, fd);
	else if (wc <= 2047)
	{
		printed += ft_putchar_fd((wc >> 6) + 0xC0, fd);
		printed += ft_putchar_fd((wc & 0x3F) + 0x80, fd);
	}
	else if (wc <= 65535)
	{
		printed += ft_putchar_fd((wc >> 12) + 0xE0, fd);
		printed += ft_putchar_fd(((wc >> 6) & 0x3F) + 0x80, fd);
		printed += ft_putchar_fd((wc & 0x3F) + 0x80, fd);
	}
	else if (wc <= 1114111)
	{
		printed += ft_putchar_fd((wc >> 18) + 0xF0, fd);
		printed += ft_putchar_fd(((wc >> 12) & 0x3F) + 0x80, fd);
		printed += ft_putchar_fd(((wc >> 6) & 0x3F) + 0x80, fd);
		printed += ft_putchar_fd((wc & 0x3F) + 0x80, fd);
	}
	return (printed);
}

int		ft_printf_cc(t_printf *pf)
{
	unsigned int	nbr;
	char			c[2];

	nbr = va_arg(pf->ap, unsigned int);
	c[0] = 'c';
	c[1] = '\0';
	pf->conv.to_sign = FALSE;
	pf->conv.space_it = FALSE;
	pf->conv.precision = 0;
	ft_printf_field_calc(pf, 1, c, NULL);
	if (!nbr && pf->conv.field_min)
		pf->conv.field_min--;
	ft_printf_field_print(pf, LEFT);
	pf->printed += ft_putwchar_fd(nbr, pf->fd);
	ft_printf_field_print(pf, RIGHT);
	return (EXIT_SUCCESS);
}

int		ft_printf_c(t_printf *pf)
{
	char	c[2];

	if (pf->conv.size >= 5)
		return (ft_printf_cc(pf));
	c[0] = (char)va_arg(pf->ap, int);
	c[1] = '\0';
	pf->conv.to_sign = FALSE;
	pf->conv.space_it = FALSE;
	pf->conv.precision = 0;
	ft_printf_field_calc(pf, 1, c, NULL);
	if (!c[0] && pf->conv.field_min > 0)
		pf->conv.field_min--;
	ft_printf_field_print(pf, LEFT);
	if (pf->conv.field_fill_char == '0')
		pf->printed += ft_print_char_xtime('0', pf->conv.precision, pf->fd);
	pf->printed += ft_putchar_fd(c[0], pf->fd);
	ft_printf_field_print(pf, RIGHT);
	return (EXIT_SUCCESS);
}
