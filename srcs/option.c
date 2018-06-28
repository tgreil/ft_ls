/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 10:57:02 by tgreil            #+#    #+#             */
/*   Updated: 2018/06/28 18:24:21 by tgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		option_is_set(unsigned char option, char option_index)
{
	unsigned char	value;

	value = 1;
	value = value << (option_index % 8);
	if (option & value)
		return (TRUE);
	return (FALSE);
}

int		option_set(unsigned char *option, char option_index)
{
	unsigned char	value;

	value = 1;
	value = value << (option_index % 8);
	*option = *option | value;
	return (E_SUCCESS);
}
