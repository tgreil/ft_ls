/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 09:56:56 by tgreil            #+#    #+#             */
/*   Updated: 2018/04/03 15:03:40 by tgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(const char *s)
{
	char	*new;
	int		size;
	int		n;
	int		i;

	i = 0;
	size = 0;
	if (!s)
		return (NULL);
	while (s[i + size] == ' ' || s[i + size] == '\t' || s[i + size] == '\n')
		i++;
	while (s[i + size])
		size++;
	size--;
	while (size >= 0 &&
			(s[i + size] == ' ' || s[i + size] == '\t' || s[i + size] == '\n'))
		size--;
	if (!(new = malloc(++size + 1)))
		return (NULL);
	n = -1;
	while (++n < size)
		new[n] = s[i + n];
	new[size] = '\0';
	return (new);
}
