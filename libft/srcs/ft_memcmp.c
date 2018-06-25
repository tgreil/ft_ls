/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 09:56:56 by tgreil            #+#    #+#             */
/*   Updated: 2018/04/03 12:35:38 by tgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*unc_s1;
	unsigned char	*unc_s2;
	size_t			i;

	i = 0;
	unc_s1 = (unsigned char *)s1;
	unc_s2 = (unsigned char *)s2;
	while (i < n)
	{
		if (unc_s1[i] != unc_s2[i])
			return (unc_s1[i] - unc_s2[i]);
		i++;
	}
	return (0);
}
