/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_pads.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaechoe <jaechoe@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:57:28 by jaechoe           #+#    #+#             */
/*   Updated: 2024/01/06 18:39:32 by jaechoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	add_pads(t_list **lst, char spec, t_vars v)
{
	char	*pads;
	size_t	len;

	if (ft_strchr("pdiuxX", spec) && (*lst)->content)
	{
		pads = padstr('0', v.prec - ft_strlen((*lst)->content));
		if (!pads)
			return (0);
		ft_lstadd_front(lst, ft_lstnew_s(pads));
	}
	ft_lstadd_front(lst, ft_lstnew_s(v.prefix));
	len = sumlen(*lst);
	if (v.ladjust)
		pads = padstr(' ', v.width - len);
	else
		pads = padstr(v.lpadc, v.width - len);
	if (!pads)
		return (0);
	if (v.ladjust)
		ft_lstadd_back(lst, ft_lstnew_s(pads));
	else
		ft_lstadd_front(lst, ft_lstnew_s(pads));
	if (ft_strchr("pdiuxX", spec) && !v.ladjust && v.lpadc == '0')
		ft_lstswap(*lst, (*lst)->next);
	return (1);
}
