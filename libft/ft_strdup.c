/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaechoe <jaechoe@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 20:38:23 by jaechoe           #+#    #+#             */
/*   Updated: 2024/01/12 21:41:13 by jaechoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dst;
	size_t	len;

	if (!s1)
		return (0);
	len = ft_strlen(s1);
	dst = malloc(len + 1);
	if (!dst)
		return (0);
	return (ft_memcpy(dst, s1, len + 1));
}
