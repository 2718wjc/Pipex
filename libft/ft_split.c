/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaechoe <jaechoe@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 21:34:54 by jaechoe           #+#    #+#             */
/*   Updated: 2024/01/23 19:24:17 by jaechoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char	*strdup_delim(const char *s1, char c)
{
	char	*dst;
	size_t	len;

	len = 0;
	while (*s1 && (*s1 != c))
	{
		len++;
		s1++;
	}
	s1 -= len;
	dst = malloc(len + 1);
	if (!dst)
		return (0);
	ft_memcpy(dst, s1, len);
	*(dst + len) = 0;
	return (dst);
}

static size_t	cnt_str(char const *s, char c)
{
	size_t	cnt;

	cnt = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			cnt++;
		while (*s && (*s != c))
			s++;
	}
	return (cnt);
}

char	**free2d(char **arr, size_t size)
{
	while (size)
	{
		free(*(arr + size - 1));
		size--;
	}
	free(arr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	char	**ptr;
	size_t	size;

	size = cnt_str(s, c);
	result = malloc((size + 1) * sizeof(char *));
	if (!result)
		return (0);
	ptr = result;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			*ptr = strdup_delim(s, c);
			if (*ptr == 0)
				return (free2d(result, ptr - result));
			ptr++;
		}
		while (*s && (*s != c))
			s++;
	}
	*ptr = 0;
	return (result);
}
