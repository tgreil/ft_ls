/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 09:56:56 by tgreil            #+#    #+#             */
/*   Updated: 2018/04/03 14:03:20 by tgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char	*c_dest;
	unsigned char	*c_src;
	size_t			i;

	i = 0;
	c_src = (unsigned char *)src;
	c_dest = (unsigned char *)dest;
	while (i < n)
	{
		c_dest[i] = c_src[i];
		if (c_src[i] == (unsigned char)c)
			return ((void *)(c_dest + i + 1));
		i++;
	}
	return (NULL);
}
