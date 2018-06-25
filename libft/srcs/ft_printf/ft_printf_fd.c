/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 15:32:43 by tgreil            #+#    #+#             */
/*   Updated: 2018/04/27 16:21:09 by tgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_printf_fd(t_printf *pf)
{
	size_t	i;

	i = pf->i + 1;
	while ((pf->str[i] >= '0' && pf->str[i] <= '9') ||
										pf->str[i] == GET_ATTR_CHAR)
		i++;
	if (pf->str[i] == FD_CHAR && i - 1 > pf->i)
	{
		if (i - pf->i == 2 && pf->str[pf->i + 1] == GET_ATTR_CHAR)
			pf->fd = va_arg(pf->ap, int);
		else
			pf->fd = ft_little_atoi(pf->str + pf->i + 1);
		pf->i = i;
	}
	else
		pf->printed += ft_putchar_fd(FD_CHAR, pf->fd);
	return (EXIT_SUCCESS);
}
