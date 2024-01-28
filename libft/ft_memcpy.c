/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaechoe <jaechoe@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:13:28 by jaechoe           #+#    #+#             */
/*   Updated: 2023/11/02 21:39:50 by jaechoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	int			*dst_i;
	const int	*src_i;
	char		*dst_c;
	const char	*src_c;

	if (dst == src)
		return (dst);
	dst_i = (int *) dst;
	src_i = (const int *) src;
	while (n >= sizeof(int))
	{
		*dst_i++ = *src_i++;
		n -= sizeof(int);
	}
	dst_c = (char *) dst_i;
	src_c = (const char *) src_i;
	while (n--)
		*dst_c++ = *src_c++;
	return (dst);
}
