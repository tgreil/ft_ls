/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 12:26:57 by tgreil            #+#    #+#             */
/*   Updated: 2018/06/25 12:57:26 by tgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <sys/stat.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <time.h>
# include <sys/xattr.h>
# include "libft.h"

# define TRUE			1
# define FALSE			0
# define E_ERROR		-1
# define E_SUCCESS		0
# define OPTION_L		0
# define OPTION_L_C		'l'
# define OPTION_RR		1
# define OPTION_RR_C	'R'
# define OPTION_A		2
# define OPTION_A_C		'a'
# define OPTION_R		3
# define OPTION_R_C		'r'
# define OPTION_T		4
# define OPTION_T_C		't'
# define LS_ERROR_MSG	"Ft_ls error: "

typedef struct			s_list_ls
{
	struct stat			stat;
	int					state;
	char				*name;
	char				name_malloced;
	struct s_list_ls	*next;
	struct s_list_ls	*prev;
}						t_list_ls;

typedef struct			s_list_manag
{
	size_t				list_len;
	t_list_ls			*start;
	t_list_ls			*act;
	t_list_ls			*end;
}						t_list_manag;

typedef struct			s_container
{
	unsigned char		option;
	t_list_manag		list_name;
}						t_container;

/*
**			main_ls.c
*/
void		ls_initializer(t_container *c);
int			main(int ac, char **av);

/*
**			ft_ls_apply.c
*/
int			ft_ls_apply_f(t_list_manag *list, t_list_ls *elem);
int			ft_ls_apply(t_container *c);

/*
**			result_print.c
*/
int			result_print(t_container *c);

/*
**			list_manag.c
*/
int			list_apply(t_list_manag *l, int (*f)(t_list_manag *, t_list_ls *));
int			list_add(t_list_manag *list, char *name);

/*
**			param_handler.c
*/
int			param_handler_option(t_container *c, char *string);
int			param_handler_file(t_container *c, char *name);
int			param_handler(t_container *c, int ac, char **av);

/*
**			option.c
*/
int			option_is_set(unsigned char option, char option_index);
int			option_set(unsigned char *option, char option_index);

#endif
