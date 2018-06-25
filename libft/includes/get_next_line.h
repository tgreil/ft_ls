/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 15:57:47 by tgreil            #+#    #+#             */
/*   Updated: 2018/04/27 16:19:17 by tgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# define READ_ERROR		-2
# define EXIT_ERROR		-1
# define EXIT_SUCCESS	0
# define BUFF_SIZE		32

typedef struct			s_gnl_one
{
	int					fd;
	char				*rest;
	int					rest_size;
}						t_gnl_one;

typedef struct			s_gnl
{
	t_gnl_one			*list;
	int					list_size;
}						t_gnl;

int						get_next_line(const int fd, char **line);

#endif
