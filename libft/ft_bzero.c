/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaechoe <jaechoe@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:08:50 by jaechoe           #+#    #+#             */
/*   Updated: 2023/10/23 18:16:31 by jaechoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	ft_bzero(void *s, size_t n)
{
	int		*s_i;
	char	*s_c;

	s_i = (int *) s;
	while (n >= sizeof(int))
	{
		*s_i++ = 0;
		n -= sizeof(int);
	}
	s_c = (char *) s_i;
	while (n--)
		*s_c++ = 0;
}
