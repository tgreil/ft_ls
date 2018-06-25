/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 15:32:58 by tgreil            #+#    #+#             */
/*   Updated: 2018/04/27 16:20:58 by tgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_printf_init(t_printf *pf, char *str)
{
	pf->i = 0;
	pf->fd = 1;
	pf->str = str;
	pf->printed = 0;
	pf->failed = FALSE;
	pf->conv.nb.data = NULL;
	pf->conv.to_sign = FALSE;
	pf->conv.field_min = 0;
	pf->conv.precision = 0;
	pf->conv.field_fill_side = LEFT;
	pf->conv.field_fill_char = DEFAULT_FILL_CHAR;
}

int			ft_printf(char *str, ...)
{
	t_printf	pf;

	va_start(pf.ap, str);
	ft_printf_init(&pf, str);
	while (str[pf.i] != '\0')
	{
		if (str[pf.i] == CONVERSION_CHAR)
		{
			if (ft_printf_conversion(&pf) < 0)
				return (EXIT_ERROR);
		}
		else if (str[pf.i] == COLOR_CHAR)
			ft_printf_color(&pf);
		else if (str[pf.i] == FD_CHAR)
			ft_printf_fd(&pf);
		else
			pf.printed += ft_putchar_fd(str[pf.i], pf.fd);
		if (str[pf.i])
			pf.i++;
	}
	va_end(pf.ap);
	return (pf.failed ? -1 : (int)pf.printed);
}
