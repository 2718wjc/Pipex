/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaechoe <jaechoe@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 20:20:06 by jaechoe           #+#    #+#             */
/*   Updated: 2023/10/23 18:46:39 by jaechoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;
	size_t	len;

	if (size && count > (size_t) -1 / size)
		return (0);
	len = count * size;
	p = malloc(len);
	if (!p)
		return (0);
	ft_bzero(p, len);
	return (p);
}
