/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conv_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 15:32:21 by tgreil            #+#    #+#             */
/*   Updated: 2018/04/27 16:31:50 by tgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_printf_conv_sign(char *s, t_pf_conversion conv)
{
	if (conv.to_sign == TRUE && s[0] == ' ')
		s[0] = '+';
}

size_t		ft_printf_conv_print(char *s, t_pf_conversion conv, int fd)
{
	if (s[0] != ' ' || conv.space_it == TRUE)
		return (ft_putstr_fd(s, fd));
	else
		return (ft_putstr_fd(s + 1, fd));
}
