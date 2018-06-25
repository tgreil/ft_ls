/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 15:22:32 by tgreil            #+#    #+#             */
/*   Updated: 2018/04/27 16:32:36 by tgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putwstr(t_printf *pf, int *s, int s_len)
{
	int		ret;
	int		nbr;

	nbr = 0;
	while (nbr < s_len)
	{
		if ((s_len - nbr >= 1 && *s <= 127) ||
			(s_len - nbr >= 2 && *s <= 2047) ||
			(s_len - nbr >= 3 && *s <= 65535) ||
			(s_len - nbr >= 4 && *s <= 1114111))
		{
			ret = ft_putwchar_fd(*s, pf->fd);
			pf->printed += ret;
		}
		nbr += ret;
		s++;
	}
}

int		ft_putwstr_calc(t_printf *pf, int *s, int s_len)
{
	int		ret;
	int		nbr;
	int		wc;

	nbr = 0;
	if (!s)
		return (0);
	while (nbr < s_len)
	{
		wc = *s;
		if (wc <= 127)
			ret = 1;
		else if (wc <= 2047)
			ret = 2;
		else if (wc <= 65535)
			ret = 3;
		else if (wc <= 1114111)
			ret = 4;
		nbr += ret;
		s++;
	}
	if (pf->conv.precision > 0 && pf->conv.field_min > 0 && s_len - nbr)
		return (s_len - nbr + ret);
	return (0);
}

int		ft_strwlen(int *s)
{
	int	ret;
	int	len;
	int	i;

	i = 0;
	len = 0;
	while (s[i])
	{
		ret = 0;
		if (s[i] <= 127)
			ret = 1;
		else if (s[i] <= 2047)
			ret = 2;
		else if (s[i] <= 65535)
			ret = 3;
		else if (s[i] <= 1114111)
			ret = 4;
		len += ret;
		i++;
	}
	return (len);
}

int		ft_printf_ss(t_printf *pf)
{
	int		s_len;
	int		*s;

	if (pf->conv.precision < 0)
		pf->conv.precision *= -1;
	s = va_arg(pf->ap, int *);
	if (s)
		s_len = ft_strwlen(s);
	else
		s_len = ft_strlen(PRINT_NULL);
	if (pf->conv.to_precis && s_len > pf->conv.precision)
		s_len = pf->conv.precision;
	pf->conv.field_min += -s_len + ft_putwstr_calc(pf, s, s_len);
	ft_printf_field_print(pf, LEFT);
	if (s && s_len > 0)
		ft_putwstr(pf, s, s_len);
	else if (s_len > 0)
		pf->printed += write(pf->fd, PRINT_NULL, s_len);
	ft_printf_field_print(pf, RIGHT);
	return (EXIT_SUCCESS);
}

int		ft_printf_s(t_printf *pf)
{
	int		s_len;
	char	*s;

	if (pf->conv.size >= 5)
		return (ft_printf_ss(pf));
	if (pf->conv.precision < 0)
		pf->conv.precision *= -1;
	s = va_arg(pf->ap, char *);
	if (s)
		s_len = ft_strlen(s);
	else
		s_len = ft_strlen(PRINT_NULL);
	if (pf->conv.to_precis && s_len > pf->conv.precision)
		s_len = pf->conv.precision;
	pf->conv.field_min -= s_len;
	ft_printf_field_print(pf, LEFT);
	if (s && s_len > 0)
		pf->printed += write(pf->fd, s, s_len);
	else if (s_len > 0)
		pf->printed += write(pf->fd, PRINT_NULL, s_len);
	ft_printf_field_print(pf, RIGHT);
	return (EXIT_SUCCESS);
}
