/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conversion.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 15:32:33 by tgreil            #+#    #+#             */
/*   Updated: 2018/04/11 14:26:15 by tgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	ft_printf_conversion_flags(t_printf *pf, size_t i)
{
	while ((pf->str[i] == ZERO_CHAR || pf->str[i] == HASHTAG_CHAR) ||
			(pf->str[i] == SUB_CHAR || pf->str[i] == ADD_CHAR) ||
			(pf->str[i] == SPACE_CHAR || pf->str[i] == QUOTE_CHAR))
	{
		if (pf->str[i] == ZERO_CHAR)
			pf->conv.field_fill_char = ZERO_CHAR;
		else if (pf->str[i] == SUB_CHAR)
			pf->conv.field_fill_side = RIGHT;
		else if (pf->str[i] == ADD_CHAR)
			pf->conv.to_sign = TRUE;
		else if (pf->str[i] == SPACE_CHAR)
			pf->conv.space_it = TRUE;
		else
			pf->conv.chang = TRUE;
		i++;
	}
	return (i);
}

static size_t	ft_printf_conversion_field(t_printf *pf, size_t i)
{
	if (pf->str[i] == GET_ATTR_CHAR)
	{
		pf->conv.field_min = va_arg(pf->ap, size_t);
		i++;
	}
	if (pf->str[i] >= '0' && pf->str[i] <= '9')
		pf->conv.field_min = ft_little_atoi(pf->str + i);
	while (pf->str[i] >= '0' && pf->str[i] <= '9')
		i++;
	if (pf->str[i] == GET_ATTR_CHAR)
		return (ft_printf_conversion_field(pf, i));
	if (pf->conv.field_min < 0)
	{
		pf->conv.field_fill_side = RIGHT;
		pf->conv.field_min = -pf->conv.field_min;
	}
	return (i);
}

static size_t	ft_printf_conversion_precision(t_printf *pf, size_t i)
{
	pf->conv.to_precis = FALSE;
	pf->conv.precision = 0;
	if (pf->str[i] == PRECISION_CHAR)
	{
		while (pf->str[i] == PRECISION_CHAR)
			i++;
		pf->conv.to_precis = TRUE;
		pf->conv.precision = ft_little_atoi(pf->str + i);
		while (pf->str[i] >= '0' && pf->str[i] <= '9')
			i++;
		if (pf->str[i] == GET_ATTR_CHAR)
		{
			pf->conv.precision = va_arg(pf->ap, size_t);
			i++;
		}
	}
	return (i);
}

static size_t	ft_printf_convesion_size(t_printf *pf, size_t i)
{
	if (pf->str[i] == H_CHAR && pf->conv.size <= 1)
	{
		pf->conv.size = 1;
		if (pf->str[i + 1] == H_CHAR && ++i)
			pf->conv.size = 2;
	}
	else if (pf->str[i] == J_CHAR && pf->conv.size <= 2)
		pf->conv.size = 3;
	else if (pf->str[i] == Z_CHAR && pf->conv.size <= 3)
		pf->conv.size = 4;
	else if (pf->str[i] == L_CHAR && pf->conv.size <= 5)
	{
		pf->conv.size = 5;
		if (pf->str[i + 1] == L_CHAR && ++i)
			pf->conv.size = 6;
	}
	else if (pf->str[i] == Q_CHAR && pf->conv.size <= 5)
		pf->conv.size = 6;
	else if (pf->str[i] == LL_CHAR && pf->conv.size <= 6)
		pf->conv.size = 7;
	if (pf->conv.size > 0)
		i++;
	return (i);
}

int				ft_printf_conversion(t_printf *pf)
{
	size_t	i;

	i = pf->i + 1;
	pf->conv.chang = FALSE;
	pf->conv.to_sign = FALSE;
	pf->conv.space_it = FALSE;
	pf->conv.field_fill_side = LEFT;
	pf->conv.field_fill_char = SPACE_CHAR;
	i = ft_printf_conversion_flags(pf, i);
	pf->conv.field_min = 0;
	i = ft_printf_conversion_field(pf, i);
	while (pf->str[i] == QUOTE_CHAR)
		i++;
	i = ft_printf_conversion_precision(pf, i);
	while (pf->str[i] == QUOTE_CHAR)
		i++;
	pf->conv.size = 0;
	while ((pf->str[i] == H_CHAR || pf->str[i] == J_CHAR) || (pf->str[i] == L_CHAR
		|| pf->str[i] == Z_CHAR) || (pf->str[i] == LL_CHAR || pf->str[i] == Q_CHAR))
		i = ft_printf_convesion_size(pf, i);
	i = ft_printf_conversion_flags(pf, i);
	ft_printf_conversion_find(pf, pf->str[i]);
	pf->i = i;
	return (EXIT_SUCCESS);
}
