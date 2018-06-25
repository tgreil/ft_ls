/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 09:56:56 by tgreil            #+#    #+#             */
/*   Updated: 2018/04/03 15:01:20 by tgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(const char *s1, const char *s2)
{
	char	*new;

	if (!s1 || !s2)
		return (NULL);
	if (!(new = malloc(ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1)))
		return (NULL);
	ft_strcpy(new, (char *)s1);
	ft_strcat(new, (char *)s2);
	return (new);
}
