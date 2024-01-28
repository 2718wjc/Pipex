/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaechoe <jaechoe@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 21:48:52 by jaechoe           #+#    #+#             */
/*   Updated: 2023/10/11 15:41:09 by jaechoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;

	len = 0;
	while (*s)
	{
		len++;
		s++;
	}
	if (!c)
		return ((char *) s);
	while (len-- != 0)
		if (*(--s) == c)
			return ((char *) s);
	return (0);
}
