/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 09:55:38 by tgreil            #+#    #+#             */
/*   Updated: 2018/04/03 12:35:53 by tgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_print_memory_first(int addr, char *base)
{
	ft_putchar(base[addr / 16 / 16 / 16 / 16 / 16 / 16 / 16 % 16]);
	ft_putchar(base[addr / 16 / 16 / 16 / 16 / 16 / 16 % 16]);
	ft_putchar(base[addr / 16 / 16 / 16 / 16 / 16 % 16]);
	ft_putchar(base[addr / 16 / 16 / 16 / 16 % 16]);
	ft_putchar(base[addr / 16 / 16 / 16 % 16]);
	ft_putchar(base[addr / 16 / 16 % 16]);
	ft_putchar(base[addr / 16 % 16]);
	ft_putchar(base[addr % 16]);
}

static void	ft_print_memory_second(unsigned char *addr, unsigned int size,
																	char *base)
{
	unsigned int	i;

	i = 0;
	ft_putchar(':');
	ft_putchar(' ');
	while (i < size && i < 16)
	{
		if (addr[i] < 16)
			ft_putchar('0');
		else
			ft_putchar(base[(addr)[i] / 16]);
		ft_putchar(base[addr[i] % 16]);
		if (i % 2)
			ft_putchar(' ');
		i++;
	}
	while (i < 16)
	{
		ft_putchar(' ');
		ft_putchar(' ');
		if (i % 2)
			ft_putchar(' ');
		i++;
	}
}

static int	ft_print_memory_third(unsigned char *addr, unsigned int size)
{
	unsigned int	i;

	i = 0;
	while (i < size && i < 16)
	{
		if (addr[i] < ' ' || addr[i] > '~')
			ft_putchar('.');
		else
			ft_putchar(addr[i]);
		i++;
	}
	return (i);
}

void		ft_print_memory(void *addr, size_t size)
{
	unsigned char	*un_addr;
	size_t			i;

	i = 0;
	un_addr = (unsigned char *)addr;
	while (i < size)
	{
		ft_print_memory_first(i, "0123456789abcdef");
		ft_print_memory_second(un_addr + i, size - i, "0123456789abcdef");
		i += ft_print_memory_third(un_addr + i, size - i);
		ft_putchar('\n');
	}
}
