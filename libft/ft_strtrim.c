/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaechoe <jaechoe@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 15:11:44 by jaechoe           #+#    #+#             */
/*   Updated: 2023/10/11 15:35:12 by jaechoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	is_in(char c, char const *set)
{
	while (*set)
		if (*set++ == c)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	char	*start;
	char	*end;
	size_t	len;

	start = (char *) s1;
	while (is_in(*start, set))
		start++;
	end = start + ft_strlen(start);
	if (end > start)
		while (is_in(*(end - 1), set))
			end--;
	len = end - start;
	result = malloc(len + 1);
	if (!result)
		return (0);
	ft_memcpy(result, start, len);
	*(result + len) = 0;
	return (result);
}
