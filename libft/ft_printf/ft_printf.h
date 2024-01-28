/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaechoe <jaechoe@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:35:26 by jaechoe           #+#    #+#             */
/*   Updated: 2024/01/06 19:38:45 by jaechoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "../libft.h"

typedef struct s_vars
{
	t_bool	ladjust;
	char	lpadc;
	char	plus_sign;
	t_bool	altfmt;
	int		width;
	int		prec;
	char	*prefix;
}	t_vars;

int			ft_printf(const char *fmt, ...);
const char	*prs(const char *fmt, t_vars *v, va_list argp);
char		*argstr(char spec, va_list argp);
char		*padstr(char padc, int cnt);
size_t		sumlen(t_list *lst);
int			truncstr(t_list *node, char spec, t_vars v);
int			add_pads(t_list **lst, char spec, t_vars v);
const char	*prnt_c(const char *fmt, t_vars v, va_list argp, int *putlen);
void		prnt_spdiux(t_list *lst, int *putlen);

#endif
