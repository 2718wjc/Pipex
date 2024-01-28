/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaechoe <jaechoe@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:17:48 by jaechoe           #+#    #+#             */
/*   Updated: 2023/10/06 17:24:24 by jaechoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	len_src;

	len_src = ft_strlen(src);
	if (dstsize == 0)
		return (len_src);
	if (dstsize < len_src + 1)
	{
		ft_memcpy(dst, src, dstsize - 1);
		*(dst + dstsize - 1) = 0;
	}
	else
		ft_memcpy(dst, src, len_src + 1);
	return (len_src);
}
