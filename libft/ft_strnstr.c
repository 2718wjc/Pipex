/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaechoe <jaechoe@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 19:04:43 by jaechoe           #+#    #+#             */
/*   Updated: 2023/10/11 19:19:37 by jaechoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	len_ndl;

	len_ndl = ft_strlen(needle);
	if (len_ndl == 0)
		return ((char *) haystack);
	if (len == 0)
		return (0);
	ft_strlen(haystack);
	while (len-- >= len_ndl)
	{
		if (*haystack == *needle)
			if (!ft_strncmp(haystack, needle, len_ndl))
				return ((char *) haystack);
		haystack++;
	}
	return (0);
}
