/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 15:57:57 by tgreil            #+#    #+#             */
/*   Updated: 2018/04/27 16:19:38 by tgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		get_next_line_init(t_gnl **p, const int fd)
{
	t_gnl_one	*new_list;
	int			i;

	i = 0;
	if (*p == NULL)
	{
		if (!((*p) = malloc(sizeof(t_gnl))))
			return (EXIT_ERROR);
		(*p)->list = NULL;
		(*p)->list_size = 0;
	}
	while (i < (*p)->list_size)
		if ((*p)->list[i++].fd == fd)
			return (i - 1);
	if (!(new_list = malloc(sizeof(t_gnl_one) * ((*p)->list_size + 1))))
		return (EXIT_ERROR);
	ft_memcpy(new_list, (*p)->list, sizeof(t_gnl_one) * (*p)->list_size);
	new_list[(*p)->list_size].fd = fd;
	new_list[(*p)->list_size].rest = NULL;
	new_list[(*p)->list_size].rest_size = 0;
	(*p)->list_size++;
	if ((*p)->list)
		free((*p)->list);
	(*p)->list = new_list;
	return ((*p)->list_size - 1);
}

int		line_is_full(char *line, int line_size)
{
	int	i;

	i = 0;
	if (!line)
		return (EXIT_ERROR);
	while (i < line_size)
	{
		if (line[i] == '\n')
			return (i);
		i++;
	}
	return (EXIT_ERROR);
}

int		get_next_line_one2(t_gnl_one *l, char **line, int size_line, int ret_r)
{
	char	*new_line;
	char	*new_rest;

	if (size_line < 0)
	{
		*line = NULL;
		if (l->rest)
			free(l->rest);
		return (0);
	}
	if (!(new_line = malloc(size_line + 1)))
		return (EXIT_ERROR);
	*line = ft_memcpy(new_line, l->rest, size_line);
	(*line)[size_line] = 0;
	if (ret_r)
	{
		if (!(new_rest = malloc(l->rest_size - size_line)))
			return (EXIT_ERROR);
		ft_memcpy(new_rest, l->rest + size_line + 1, l->rest_size - size_line);
		free(l->rest);
		l->rest = new_rest;
		l->rest_size = l->rest_size - size_line - 1;
	}
	return (ret_r);
}

int		get_next_line_one(t_gnl_one *l, const int fd, char **line)
{
	char	buf[BUFF_SIZE];
	int		ret_r;
	char	*tmp;
	int		i;

	ret_r = 1;
	while (ret_r && (i = line_is_full(l->rest, l->rest_size)) == EXIT_ERROR)
	{
		if ((ret_r = read(fd, buf, BUFF_SIZE)) < 0)
			return (EXIT_ERROR);
		if (!(tmp = malloc(l->rest_size + ret_r + 1)))
			return (EXIT_ERROR);
		if (l->rest)
			ft_memcpy(tmp, l->rest, l->rest_size);
		ft_memcpy(tmp + l->rest_size, buf, ret_r);
		if (l->rest)
			free(l->rest);
		l->rest = tmp;
		l->rest_size += ret_r;
	}
	if (i < 0 && ret_r == 0 && l->rest_size)
		i = l->rest_size;
	return (get_next_line_one2(l, line, i, ret_r));
}

int		get_next_line(const int fd, char **line)
{
	static t_gnl	*p = NULL;
	t_gnl_one		*tmp;
	int				rank;
	int				ret_r;

	if (fd < 0 || !line || (rank = get_next_line_init(&p, fd)) == EXIT_ERROR)
		return (EXIT_ERROR);
	if ((ret_r = get_next_line_one(&(p->list[rank]), fd, line)) == EXIT_ERROR)
		return (EXIT_ERROR);
	if (ret_r > 0)
		return (1);
	if (!(tmp = malloc(sizeof(t_gnl_one) * (p->list_size - 1))))
		return (EXIT_ERROR);
	ft_memcpy(tmp, p->list, sizeof(t_gnl_one) * rank);
	ft_memcpy(&(tmp[rank]), &(p->list[rank + 1]),
								sizeof(t_gnl_one) * (p->list_size - rank - 1));
	free(p->list);
	p->list = tmp;
	if (--p->list_size == 0)
	{
		free(tmp);
		free(p);
		p = NULL;
	}
	return ((*line ? 1 : 0));
}
