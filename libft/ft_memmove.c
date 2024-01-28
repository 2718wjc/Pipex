/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaechoe <jaechoe@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:30:44 by jaechoe           #+#    #+#             */
/*   Updated: 2023/10/07 20:03:05 by jaechoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int			*dst_i;
	const int	*src_i;
	char		*dst_c;
	const char	*src_c;

	if (dst == src)
		return (dst);
	if (dst < src)
		return (ft_memcpy(dst, src, len));
	dst_i = (int *)((char *) dst + len);
	src_i = (const int *)((char *) src + len);
	while (len >= sizeof(int))
	{
		*(--dst_i) = *(--src_i);
		len -= sizeof(int);
	}
	dst_c = (char *) dst_i;
	src_c = (const char *) src_i;
	while (len-- != 0)
		*(--dst_c) = *(--src_c);
	return (dst);
}
