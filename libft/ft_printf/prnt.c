/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prnt.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaechoe <jaechoe@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 20:43:16 by jaechoe           #+#    #+#             */
/*   Updated: 2024/01/06 18:39:01 by jaechoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

const char	*prnt_c(const char *fmt, t_vars v, va_list argp, int *putlen)
{
	char	*pads;

	if (!v.ladjust)
	{
		pads = padstr(v.lpadc, v.width - 1);
		if (!pads)
			return (0);
		ft_putstr_fd(pads, 1);
	}
	if (*fmt == 'c')
		ft_putchar_fd(va_arg(argp, int), 1);
	else
		ft_putchar_fd('%', 1);
	if (v.ladjust)
	{
		pads = padstr(' ', v.width - 1);
		if (!pads)
			return (0);
		ft_putstr_fd(pads, 1);
	}
	*putlen += ft_strlen(pads) + 1;
	free(pads);
	return (++fmt);
}

void	prnt_spdiux(t_list *lst, int *putlen)
{
	t_list	*node;

	node = lst;
	while (node)
	{
		if (node->content)
			ft_putstr_fd(node->content, 1);
		node = node->next;
	}
	*putlen += sumlen(lst);
	ft_lstclear(&lst, free);
}
