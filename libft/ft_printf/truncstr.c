/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   truncstr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaechoe <jaechoe@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:56:19 by jaechoe           #+#    #+#             */
/*   Updated: 2024/01/06 18:39:56 by jaechoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

int	truncstr(t_list *node, char spec, t_vars v)
{
	size_t	len;

	if (spec == 's')
	{
		if (!node->content)
			node->content = "(null)";
		len = ft_strlen(node->content);
		if (len > 0x7fffffff)
			len = 0x7fffffff;
		if (v.prec > -1 && (size_t) v.prec < len)
			node->content = ft_substr(node->content, 0, v.prec);
		else
			node->content = ft_substr(node->content, 0, len);
		if (!node->content)
			return (0);
	}
	else if (ft_strchr("pdiuxX", spec))
	{
		if (*(char *) node->content == '0' && !v.prec)
		{
			free(node->content);
			node->content = 0;
		}
	}
	return (1);
}
