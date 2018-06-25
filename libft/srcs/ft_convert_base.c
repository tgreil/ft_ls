/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 14:25:53 by tgreil            #+#    #+#             */
/*   Updated: 2018/04/03 18:28:07 by tgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

static int	ft_getnbr(const char *nb, const char *base, int len)
{
	int	is_neg;
	int	total;
	int	i;

	total = 0;
	is_neg = 1;
	if (*nb == '-')
	{
		is_neg = -1;
		nb++;
	}
	while (*nb)
	{
		i = 0;
		while (base[i] && base[i] != *nb)
			i++;
		total = total * len + i;
		nb++;
	}
	return (total * is_neg);
}

static void	ft_convert_base_2_fill(int nb, const char *base, int new_len,
																	char *new)
{
	int	i;
	int	tmp;
	int	base_len;

	base_len = 0;
	while (base[base_len])
		base_len++;
	if (nb < 0)
	{
		new_len--;
		*new = '-';
		nb *= -1;
		new++;
	}
	while (new_len)
	{
		i = 1;
		tmp = nb;
		while (i++ < new_len)
			tmp = tmp / base_len;
		*new = base[tmp % base_len];
		new++;
		new_len--;
	}
	*new = '\0';
}

static char	*ft_convert_base_2(int nb, const char *base, int len)
{
	char	*new;
	int		tmp;
	int		new_len;

	if (nb < 0)
		new_len = 3;
	else
		new_len = 2;
	tmp = nb;
	if (tmp < 0)
		tmp *= -1;
	while (tmp >= len)
	{
		tmp = tmp / len;
		new_len++;
	}
	if (!(new = malloc(new_len)))
		return (NULL);
	ft_convert_base_2_fill(nb, base, new_len - 1, new);
	return (new);
}

char		*ft_convert_base(const char *nbr, const char *base_from,
															const char *base_to)
{
	int	nb;
	int	from_len;
	int	to_len;

	to_len = 0;
	from_len = 0;
	while (base_from[from_len])
		from_len++;
	while (base_to[to_len])
		to_len++;
	nb = ft_getnbr(nbr, base_from, from_len);
	return (ft_convert_base_2(nb, base_to, to_len));
}
