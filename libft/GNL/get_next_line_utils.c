/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaechoe <jaechoe@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 17:42:19 by jaechoe           #+#    #+#             */
/*   Updated: 2023/11/06 21:53:14 by jaechoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*new_node(void *content, t_type type)
{
	t_file	*fl;
	t_list	*node;

	if (type == FILE_NODE)
	{
		fl = malloc(sizeof(t_file));
		if (!fl)
			return (NULL);
		fl->fd = *(int *) content;
		fl->save = NULL;
		fl->len_save = 0;
		content = fl;
	}
	node = malloc(sizeof(t_list));
	if (!node)
	{
		free(content);
		return (NULL);
	}
	node->content = content;
	node->next = NULL;
	return (node);
}

t_list	*append_node(t_list **lst, t_list *lastnode, t_list *new)
{
	if (!new)
		return (NULL);
	if (*lst == NULL)
	{
		*lst = new;
		return (new);
	}
	lastnode->next = new;
	return (new);
}

size_t	get_idx_nl(const char *s, size_t len)
{
	size_t	i;

	if (!len)
		return ((size_t) - 1);
	i = 0;
	while (i < len)
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (i);
}

void	*ft_memcpy_s(void *dst, const void *src, size_t n)
{
	int			*dst_i;
	const int	*src_i;
	char		*dst_c;
	const char	*src_c;

	if (!dst || !src || !n)
		return (NULL);
	if (dst == src)
		return (dst);
	dst_i = (int *) dst;
	src_i = (const int *) src;
	while (n >= sizeof(int))
	{
		*dst_i++ = *src_i++;
		n -= sizeof(int);
	}
	dst_c = (char *) dst_i;
	src_c = (const char *) src_i;
	while (n--)
		*dst_c++ = *src_c++;
	return (dst);
}

void	remove_fnode(t_list **flst, int fd)
{
	t_list	*fnode;
	t_list	*prev;

	fnode = *flst;
	if (!fnode)
		return ;
	if (((t_file *) fnode->content)->fd == fd)
		*flst = (*flst)->next;
	else
	{
		while (fnode && ((t_file *) fnode->content)->fd != fd)
		{
			prev = fnode;
			fnode = fnode->next;
		}
		if (!fnode)
			return ;
		prev->next = fnode->next;
	}
	free(((t_file *) fnode->content)->save);
	free(fnode->content);
	free(fnode);
}
