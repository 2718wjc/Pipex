/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaechoe <jaechoe@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:51:49 by jaechoe           #+#    #+#             */
/*   Updated: 2024/01/23 20:22:35 by jaechoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup_s(const char *s1)
{
	char	*dst;
	size_t	len;

	if (!s1)
		len = 0;
	else
		len = ft_strlen(s1);
	dst = malloc(len + 1);
	while (!dst)
		dst = malloc(len + 1);
	if (!s1)
	{
		*dst = '\0';
		return (dst);
	}
	return (ft_memcpy(dst, s1, len + 1));
}
