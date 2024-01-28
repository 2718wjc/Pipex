/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaechoe <jaechoe@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:57:29 by jaechoe           #+#    #+#             */
/*   Updated: 2023/10/23 18:17:00 by jaechoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	val;
	unsigned char	*b_c;

	val = (unsigned char) c;
	b_c = (unsigned char *) b;
	while (len--)
		*b_c++ = val;
	return (b);
}
