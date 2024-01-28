/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaechoe <jaechoe@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:36:49 by jaechoe           #+#    #+#             */
/*   Updated: 2024/01/06 18:39:15 by jaechoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static const char	*set_flag(const char *fmt, t_vars *v)
{
	if (*fmt == '-' && !v->ladjust)
		v->ladjust = TRUE;
	else if (*fmt == '0' && v->lpadc == ' ')
		v->lpadc = '0';
	else if (*fmt == '+' && v->plus_sign != '+')
		v->plus_sign = '+';
	else if (*fmt == ' ' && v->plus_sign != ' ' && v->plus_sign != '+')
		v->plus_sign = ' ';
	else if (*fmt == '#' && !v->altfmt)
		v->altfmt = TRUE;
	return (++fmt);
}

static const char	*set_width_prec(const char *fmt, t_vars *v)
{
	if (ft_isdigit(*fmt))
	{
		v->width = ft_atoi(fmt);
		while (ft_isdigit(*fmt))
			fmt++;
	}
	else if (*fmt == '.')
	{
		v->prec = 0;
		fmt++;
		if (ft_isdigit(*fmt))
		{
			v->prec = ft_atoi(fmt);
			while (ft_isdigit(*fmt))
				fmt++;
		}
	}
	return (fmt);
}

static void	ignore_flag(char spec, t_vars *v, va_list argp)
{
	va_list	copy;

	if (ft_strchr("pdiuxX", spec) && v->prec > -1)
		v->lpadc = ' ';
	if (spec == 'x' || spec == 'X')
	{
		va_copy(copy, argp);
		if (!va_arg(copy, unsigned int))
			v->altfmt = FALSE;
		va_end(copy);
	}
}

static void	set_prefix(char spec, t_vars *v, va_list argp)
{
	va_list	copy;

	if (spec == 'd' || spec == 'i')
	{
		va_copy(copy, argp);
		if (va_arg(copy, int) < 0)
			v->prefix = ft_strdup_s("-");
		else
			if (v->plus_sign)
				v->prefix = padstr(v->plus_sign, 1);
		va_end(copy);
	}
	else if (spec == 'p' || (spec == 'x' && v->altfmt))
		v->prefix = ft_strdup_s("0x");
	else if (spec == 'X' && v->altfmt)
		v->prefix = ft_strdup_s("0X");
}

const char	*prs(const char *fmt, t_vars *v, va_list argp)
{
	while (*fmt && ft_strchr("-0+ #.123456789", *fmt))
	{
		if (ft_strchr("-0+ #", *fmt))
			fmt = set_flag(fmt, v);
		else
			fmt = set_width_prec(fmt, v);
	}
	if (v->width < 0 || v->prec < -1)
		return (0);
	if (!*fmt || !ft_strchr("cspdiuxX%", *fmt))
		return (fmt);
	ignore_flag(*fmt, v, argp);
	set_prefix(*fmt, v, argp);
	return (fmt);
}
