/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 15:32:11 by tgreil            #+#    #+#             */
/*   Updated: 2018/04/27 16:26:53 by tgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# include <stdarg.h>

# define ABS(n)				n < 0 ? -n : n
# define EXIT_ERROR			-1
# define EXIT_SUCCESS		0
# define EXIT_S				EXIT_SUCCESS
# define STD_OUT			1
# define STD_ERROR			2
# define TRUE				1
# define FALSE				0
# define LEFT				22
# define RIGHT				12
# define GET_ATTR_CHAR		'*'
# define G_A_C				GET_ATTR_CHAR
# define CONVERSION_CHAR	'%'
# define COLOR_CHAR			'{'
# define COLOR_CHAR_END		'}'
# define COLOR_SIZE			5
# define FD_CHAR			'!'
# define FILE_CHAR			'$'
# define DEFAULT_FILL_CHAR	' '
# define HASHTAG_CHAR		'#'
# define ZERO_CHAR			'0'
# define SUB_CHAR			'-'
# define ADD_CHAR			'+'
# define SPACE_CHAR			' '
# define PRECISION_CHAR		'.'
# define L_CHAR				'l'
# define LL_CHAR			'L'
# define H_CHAR				'h'
# define Z_CHAR				'z'
# define J_CHAR				'j'
# define Q_CHAR				'q'
# define QUOTE_CHAR			'\''
# define PRINT_NULL			"(null)"

typedef struct				s_pf_nb
{
	void					*data;
}							t_pf_nb;

typedef struct				s_pf_conversion
{
	t_pf_nb					nb;
	char					size;
	char					chang;
	char					to_sign;
	char					space_it;
	int						precision;
	char					to_precis;
	int						field_min;
	char					field_fill_char;
	char					field_fill_side;
}							t_pf_conversion;

typedef struct				s_printf
{
	int						fd;
	t_pf_conversion			conv;
	va_list					ap;
	size_t					i;
	char					*str;
	size_t					printed;
	char					failed;
}							t_printf;

int							ft_print_char_xtime(char c, int nbr, int fd);
int							ft_putwchar_fd(unsigned int c, int fd);
char						*ft_strndup(char *str, size_t n);
int							ft_little_atoi(char *str);
char						*ft_llong_itoa(unsigned long long nb, char *base);

int							ft_printf_b(t_printf *pf);
int							ft_printf_c(t_printf *pf);
int							ft_printf_cc(t_printf *pf);
int							ft_printf_d(t_printf *pf);
int							ft_printf_dd(t_printf *pf);
int							ft_printf_i(t_printf *pf);
int							ft_printf_n(t_printf *pf);
int							ft_printf_o(t_printf *pf);
int							ft_printf_oo(t_printf *pf);
int							ft_printf_p(t_printf *pf);
int							ft_printf_s(t_printf *pf);
int							ft_printf_ss(t_printf *pf);
int							ft_printf_u(t_printf *pf);
int							ft_printf_uu(t_printf *pf);
int							ft_printf_x(t_printf *pf);
int							ft_printf_xx(t_printf *pf);
int							ft_printf_xxx(t_printf *p, char *b, char *r, int f);
int							ft_printf_mod(t_printf *pf);

void						ft_printf_field_calc(t_printf *p, long long nbr,
													char *c_nbr, char *prefix);
void						ft_printf_sign_print(t_printf *pf, char is_neg);
void						ft_printf_field_print(t_printf *pf, char s);
long long					ft_printf_type_get(t_printf *pf, char type, char u);
void						ft_printf_conv_sign(char *s, t_pf_conversion c);
int							ft_printf_conversion_find(t_printf *p, char c);
int							ft_printf_fd(t_printf *pf);
int							ft_printf_color(t_printf *pf);
int							ft_printf_conversion(t_printf *pf);
int							ft_printf(char *s, ...);

#endif
