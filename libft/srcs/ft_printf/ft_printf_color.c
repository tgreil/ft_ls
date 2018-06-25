/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 15:32:18 by tgreil            #+#    #+#             */
/*   Updated: 2018/04/27 16:30:27 by tgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_printf_is_color(char *color, char *compar)
{
	size_t		i;

	i = 0;
	while (color[i] || compar[i])
	{
		if (color[i] != compar[i])
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static char		*ft_printf_color_get2(char *color_name, char *color, int to_f)
{
	if (ft_printf_is_color("light gray", color_name) == TRUE)
		color = ft_strndup("\e[90m", COLOR_SIZE);
	if (ft_printf_is_color("light red", color_name) == TRUE)
		color = ft_strndup("\e[91m", COLOR_SIZE);
	if (ft_printf_is_color("light green", color_name) == TRUE)
		color = ft_strndup("\e[92m", COLOR_SIZE);
	if (ft_printf_is_color("light yellow", color_name) == TRUE)
		color = ft_strndup("\e[93m", COLOR_SIZE);
	if (ft_printf_is_color("light blue", color_name) == TRUE)
		color = ft_strndup("\e[94m", COLOR_SIZE);
	if (ft_printf_is_color("light magenta", color_name) == TRUE)
		color = ft_strndup("\e[95m", COLOR_SIZE);
	if (ft_printf_is_color("light cyan", color_name) == TRUE)
		color = ft_strndup("\e[96m", COLOR_SIZE);
	if (ft_printf_is_color("white", color_name) == TRUE)
		color = ft_strndup("\e[97m", COLOR_SIZE);
	if (to_f == TRUE)
		free(color_name);
	return (color);
}

static char		*ft_printf_color_get(char *color_name, int to_free)
{
	char		*color;

	color = NULL;
	if (ft_printf_is_color("eoc", color_name) == TRUE)
		color = ft_strndup("\e[39m", COLOR_SIZE);
	if (ft_printf_is_color("black", color_name) == TRUE)
		color = ft_strndup("\e[30m", COLOR_SIZE);
	if (ft_printf_is_color("red", color_name) == TRUE)
		color = ft_strndup("\e[31m", COLOR_SIZE);
	if (ft_printf_is_color("green", color_name) == TRUE)
		color = ft_strndup("\e[32m", COLOR_SIZE);
	if (ft_printf_is_color("yellow", color_name) == TRUE)
		color = ft_strndup("\e[33m", COLOR_SIZE);
	if (ft_printf_is_color("blue", color_name) == TRUE)
		color = ft_strndup("\e[34m", COLOR_SIZE);
	if (ft_printf_is_color("magenta", color_name) == TRUE)
		color = ft_strndup("\e[35m", COLOR_SIZE);
	if (ft_printf_is_color("cyan", color_name) == TRUE)
		color = ft_strndup("\e[36m", COLOR_SIZE);
	return (ft_printf_color_get2(color_name, color, to_free));
}

int				ft_printf_color(t_printf *pf)
{
	char	*color_name;
	char	*color;
	size_t	i;

	i = pf->i + 1;
	while (pf->str[i] && pf->str[i] != COLOR_CHAR_END)
		i++;
	if (pf->str[i] == COLOR_CHAR_END)
	{
		if (i - pf->i == 2 && pf->str[pf->i + 1] == GET_ATTR_CHAR)
			color_name = va_arg(pf->ap, char *);
		else
			color_name = ft_strndup(pf->str + pf->i + 1, i - pf->i - 1);
		if ((color = ft_printf_color_get(color_name, pf->str[i - 1] != G_A_C)))
		{
			if (pf->fd == STD_OUT || pf->fd == STD_ERROR)
				write(pf->fd, color, COLOR_SIZE);
			free(color);
			pf->i = i;
		}
	}
	if (pf->i != i)
		pf->printed += ft_putchar_fd(pf->str[pf->i], pf->fd);
	return (EXIT_SUCCESS);
}
