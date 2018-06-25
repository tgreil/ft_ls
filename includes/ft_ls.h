/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 12:26:57 by tgreil            #+#    #+#             */
/*   Updated: 2018/06/25 10:21:20 by tgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"

# define TRUE			1
# define FALSE			0
# define E_ERROR		-1
# define E_SUCCESS		0

typedef struct			s_list_ls
{
	void				*data;
	struct s_list_ls	*next;
	struct s_list_ls	*prev;
}						t_list_ls;

typedef struct			s_list_manag
{
	size_t				list_len;
	t_list_ls			*start;
	t_list_ls			*end;
}						t_list_manag;

#endif
