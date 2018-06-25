/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 09:21:28 by tgreil            #+#    #+#             */
/*   Updated: 2018/04/03 18:25:12 by tgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	check_base(const char *base)
{
	int	size;
	int	i;

	size = 0;
	while (base[size])
	{
		i = 0;
		if (base[size] == '-' || base[size] == '+')
			return (0);
		while (base[i])
		{
			if (base[i] == base[size] && i != size)
				return (0);
			i++;
		}
		size++;
	}
	if (size < 2)
		return (0);
	return (1);
}

static int	check_str(const char *str, const char *base, int base_len)
{
	int	i_str;
	int	i_base;

	if (!str || !*str)
		return (0);
	i_str = 0;
	while (str[i_str])
	{
		i_base = 0;
		while (base[i_base] && base[i_base] != str[i_str])
			i_base++;
		if (i_base == base_len && str[i_str] != '+' && str[i_str] != '-')
			return (0);
		i_str++;
	}
	return (1);
}

static int	ft_atoi_base_rec(const char *str, const char *base,
												int base_len, int neg_value)
{
	int	nbr;
	int	i_base;

	nbr = 0;
	while (*str)
	{
		i_base = 0;
		while (i_base < base_len && base[i_base] != *str)
			i_base++;
		if (i_base == base_len)
			return (nbr);
		nbr *= base_len;
		nbr += (i_base * neg_value);
		str++;
	}
	return (nbr);
}

int			ft_atoi_base(const char *str, char *base)
{
	int	base_len;
	int	neg_value;

	base_len = 0;
	neg_value = 1;
	if (!base)
		return (0);
	while (base[base_len])
		base_len++;
	if (!check_base(base) || !check_str(str, base, base_len))
		return (0);
	if (*str == '-')
	{
		neg_value = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	return (ft_atoi_base_rec(str, base, base_len, neg_value));
}
