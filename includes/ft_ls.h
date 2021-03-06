/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 12:26:57 by tgreil            #+#    #+#             */
/*   Updated: 2018/06/30 19:24:01 by tgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <uuid/uuid.h>
# include <time.h>
# include <sys/xattr.h>
# include <sys/acl.h>
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
# define OPTION_C		5
# define OPTION_C_C		'c'
# define LS_ERROR_MSG	"Ft_ls error: "

typedef struct s_list_ls		t_list_ls;
typedef struct s_list_manag		t_list_manag;

typedef struct			s_list_manag
{
	int					calc[5];
	size_t				list_len;
	char				*path;
	t_list_ls			*start;
	t_list_ls			*act;
	t_list_manag		*next;
	t_list_ls			*from;
	int					level;
}						t_list_manag;

typedef struct			s_list_ls
{
	struct group 		*group;
	struct passwd		*passwd;
	struct stat			stat;
	int					state;
	struct dirent		*dirent;
	DIR					*dir_dir;
	char				*name;
	char				*name_pathed;
	struct s_list_manag	folder;
	struct s_list_manag	*list;
	struct s_list_ls	*next;
	struct s_list_ls	*prev;
}						t_list_ls;

typedef struct			s_container
{
	unsigned char		option;
	t_list_manag		list_param;
}						t_container;

/*
**			main_ls.c
*/
void		ls_initializer(t_container *c);
int			ls_function(t_container *c, t_list_manag *list);
int			ls_exit(t_list_manag *list, int status);
int			main(int ac, char **av);

/*
**			ft_ls_apply.c
*/
int			ft_ls_apply(t_container *c, t_list_manag *list);

/*
**			result_print.c
*/
char		print_right_more(t_list_ls *elem);
int			print_rights(t_list_ls *elem);
int			print_option_l(t_list_ls *elem);
int			print_result_unit(t_container *c, t_list_ls *elem);
int			print_result(t_container *c, t_list_manag *list);

/*
**			list_manag.c
*/
void		list_swap(t_list_manag *list, t_list_ls *prev, t_list_ls *act);
void		list_sort(t_list_manag *list, int sens,
									int (*f)(t_list_ls *, t_list_ls *));
t_list_ls	*list_create(t_list_manag *list, char *name);
int			list_calc(t_list_manag *list, t_list_ls *new);
int			list_add(t_list_manag *list, char *name);

/*
**			param_handler.c
*/
int			param_handler_option(t_container *c, char *string);
int			param_handler_file(t_container *c, char *name);
int			param_handler(t_container *c, int ac, char **av);

/*
**			sort.c
*/
int			sort_date(t_list_ls *one, t_list_ls *two);
int			sort_name(t_list_ls *one, t_list_ls *two);

/*
**			option.c
*/
int			option_is_set(unsigned char option, char option_index);
int			option_set(unsigned char *option, char option_index);

/*
**			ls_utils.c
*/
int			int_get_unit(int nb);

#endif
