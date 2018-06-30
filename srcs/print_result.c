/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_result.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 11:57:43 by tgreil            #+#    #+#             */
/*   Updated: 2018/06/30 14:12:42 by tgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		print_rights(t_list_ls *elem)
{
	acl_entry_t	dummy;
	acl_t		acl;

	if ((elem->stat.st_mode & S_IFDIR))
		ft_printf("%c", S_ISDIR(elem->stat.st_mode) ? 'd' : '-');
	else
		ft_printf("%c", S_ISLNK(elem->stat.st_mode) ? 'l' : '-');
	ft_printf("%c", (elem->stat.st_mode & S_IRUSR) ? 'r' : '-');
	ft_printf("%c", (elem->stat.st_mode & S_IWUSR) ? 'w' : '-');
	ft_printf("%c", (elem->stat.st_mode & S_IXUSR) ? 'x' : '-');
	ft_printf("%c", (elem->stat.st_mode & S_IRGRP) ? 'r' : '-');
	ft_printf("%c", (elem->stat.st_mode & S_IWGRP) ? 'w' : '-');
	ft_printf("%c", (elem->stat.st_mode & S_IXGRP) ? 'x' : '-');
	ft_printf("%c", (elem->stat.st_mode & S_IROTH) ? 'r' : '-');
	ft_printf("%c", (elem->stat.st_mode & S_IWOTH) ? 'w' : '-');
	ft_printf("%c", (elem->stat.st_mode & S_IXOTH) ? 'x' : '-');
	acl = acl_get_link_np(elem->name_pathed, ACL_TYPE_EXTENDED);
	if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &dummy) == -1)
		acl = NULL; // acl_free(acl);
	if (listxattr(elem->name_pathed, NULL, 0, XATTR_NOFOLLOW) > 0)
		ft_printf("@");
	else
		ft_printf("%c", acl != NULL ? '+' : ' ');
	return (E_SUCCESS);
}

int		print_option_l(t_list_ls *elem)
{
	char	*date;

	print_rights(elem);
	ft_printf("%*d ", elem->list->calc[1] + 1, elem->stat.st_nlink);
	ft_printf("%*s ", elem->list->calc[2], elem->passwd->pw_name);
	ft_printf("%*s ", elem->list->calc[3] + 1, elem->group->gr_name);
	ft_printf("%*d ", elem->list->calc[4] + 1, elem->stat.st_size);
	date = ctime(&elem->stat.st_mtime);
	date += 4;
	date[ft_strlen(date) - 1] = '\0';
	if (ft_strcmp(date + ft_strlen(date) - 5, " 2018"))
	{
		ft_printf("%.7s ", date);
		ft_printf("%s ", date + ft_strlen(date) - 4);
	}
	else
		ft_printf("%.12s ", date);
	return (E_SUCCESS);
}

int		print_name(t_list_ls *elem, int option)
{
	if (option_is_set(option, OPTION_C))
	{
		if ((elem->stat.st_mode & S_IFDIR))
			ft_printf("{light blue}");
		else if (S_ISLNK(elem->stat.st_mode))
			ft_printf("{light magenta}");
		else if ((elem->stat.st_mode & S_IXUSR))
			ft_printf("{light red}");
	}
	ft_printf("%s", elem->name);
	if (option_is_set(option, OPTION_C))
		ft_printf("{eoc}");
	return (E_SUCCESS);
}

int		print_result_unit(t_container *c, t_list_ls *elem)
{
	char	buf[1024];
	int		ret;

	if (option_is_set(c->option, OPTION_L))
		print_option_l(elem);
	print_name(elem, c->option);
	ret = readlink(elem->name_pathed, buf, 1023);
	if (S_ISLNK(elem->stat.st_mode))
		ft_printf(" -> %.*s", ret, buf);
	ft_printf("\n");
	return (E_SUCCESS);
}

int		print_result(t_container *c, t_list_manag *list)
{
	list->act = list->start;
	if (list->from && list->from->list->level)
		if (list->list_len > 0)
			ft_printf("\n%s:\n", list->from->name_pathed);
	if (list->level && option_is_set(c->option, OPTION_L))
		ft_printf("total %d\n", list->calc[0]);
	while (list->act)
	{
		if (list->level > 0 || (list->level == 0 &&
								!(list->act->stat.st_mode & S_IFDIR)))
			print_result_unit(c, list->act);
		list->act = list->act->next;
	}
	return (E_SUCCESS);
}
