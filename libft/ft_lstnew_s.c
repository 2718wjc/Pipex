/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaechoe <jaechoe@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:21:23 by jaechoe           #+#    #+#             */
/*   Updated: 2024/01/06 17:21:41 by jaechoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstnew_s(void *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	while (!node)
		node = malloc(sizeof(t_list));
	node->content = content;
	node->next = 0;
	return (node);
}
