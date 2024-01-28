/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstswap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaechoe <jaechoe@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:52:08 by jaechoe           #+#    #+#             */
/*   Updated: 2023/10/23 15:55:03 by jaechoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstswap(t_list *node1, t_list *node2)
{
	void	*temp;

	temp = node1->content;
	node1->content = node2->content;
	node2->content = temp;
}
