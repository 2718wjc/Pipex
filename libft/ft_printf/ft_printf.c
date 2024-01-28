/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaechoe <jaechoe@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:55:44 by jaechoe           #+#    #+#             */
/*   Updated: 2024/01/06 18:38:27 by jaechoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ft_printf.h"

static const char	*prnt_arg(const char *fmt, va_list argp, int *putlen)
{
	t_vars	v;
	t_list	*lst;

	v = (t_vars){FALSE, ' ', 0, FALSE, 0, -1, NULL};
	fmt = prs(fmt, &v, argp);
	if (!fmt)
		return (0);
	if (!*fmt || !ft_strchr("cspdiuxX%", *fmt))
		return (fmt);
	if (*fmt == 'c' || *fmt == '%')
		return (prnt_c(fmt, v, argp, putlen));
	lst = ft_lstnew_s(argstr(*fmt, argp));
	if (!truncstr(lst, *fmt, v) || !add_pads(&lst, *fmt, v))
	{
		ft_lstclear(&lst, free);
		return (0);
	}
	prnt_spdiux(lst, putlen);
	return (++fmt);
}

static const char	*prnt_nonarg(const char *fmt, int *putlen)
{
	const char	*str;
	size_t		len;

	str = fmt;
	while (*fmt && *fmt != '%')
		fmt++;
	len = fmt - str;
	if (len > 0x7fffffff)
		len = 0x7fffffff;
	write(1, str, len);
	*putlen += len;
	return (fmt);
}

int	ft_printf(const char *fmt, ...)
{
	va_list	argp;
	int		putlen;

	va_start(argp, fmt);
	putlen = 0;
	while (*fmt)
	{
		if (*fmt == '%')
			fmt = prnt_arg(++fmt, argp, &putlen);
		else
			fmt = prnt_nonarg(fmt, &putlen);
		if (!fmt || putlen < 0)
		{
			putlen = -1;
			break ;
		}
	}
	va_end(argp);
	return (putlen);
}
