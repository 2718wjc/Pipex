/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaechoe <jaechoe@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 20:26:04 by jaechoe           #+#    #+#             */
/*   Updated: 2023/10/11 20:25:56 by jaechoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len_dst;
	size_t	len_src;

	len_src = ft_strlen(src);
	if (dstsize == 0)
		return (len_src);
	len_dst = ft_strlen(dst);
	if (dstsize < len_dst + 1)
		return (dstsize + len_src);
	if (dstsize < len_dst + len_src + 1)
	{
		ft_memcpy(dst + len_dst, src, dstsize - len_dst - 1);
		*(dst + dstsize - 1) = 0;
	}
	else
		ft_memcpy(dst + len_dst, src, len_src + 1);
	return (len_dst + len_src);
}
