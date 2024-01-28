/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaechoe <jaechoe@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 20:56:48 by jaechoe           #+#    #+#             */
/*   Updated: 2023/10/25 16:41:16 by jaechoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;

	if (!s)
		return (0);
	while (start--)
		if (!*++s)
			return (ft_calloc(1, sizeof(char)));
	if (len >= ft_strlen(s))
		return (ft_strdup(s));
	dst = malloc(len + 1);
	if (!dst)
		return (0);
	ft_memcpy(dst, s, len);
	*(dst + len) = 0;
	return (dst);
}
