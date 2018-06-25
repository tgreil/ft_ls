/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 09:56:56 by tgreil            #+#    #+#             */
/*   Updated: 2018/04/03 12:34:42 by tgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_itoa_getsize(int nb)
{
	int	size;

	size = 0;
	if (!nb)
		return (1);
	if (nb < 0)
	{
		nb = -nb;
		size++;
	}
	while (nb)
	{
		size++;
		nb = nb / 10;
	}
	return (size);
}

char		*ft_itoa(int nb)
{
	char	*new;
	size_t	len;
	size_t	i;

	if (nb == INT_MIN)
		return (ft_strdup("-2147483648"));
	len = ft_itoa_getsize(nb);
	if (!(new = malloc(len + 1)))
		return (NULL);
	i = 0;
	if (nb < 0)
	{
		new[i++] = '-';
		nb = -nb;
	}
	new[len] = '\0';
	while (i < len)
	{
		new[len - 1] = nb % 10 + '0';
		nb = nb / 10;
		len--;
	}
	return (new);
}
