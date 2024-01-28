/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaechoe <jaechoe@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:02:53 by jaechoe           #+#    #+#             */
/*   Updated: 2023/10/10 22:39:26 by jaechoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	val;
	unsigned char	*s_c;

	val = (unsigned char) c;
	s_c = (unsigned char *) s;
	while (n-- != 0)
	{
		if (*s_c == val)
			return ((void *) s_c);
		s_c++;
	}
	return (0);
}
