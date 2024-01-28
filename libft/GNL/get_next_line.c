/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaechoe <jaechoe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 17:06:13 by jaechoe           #+#    #+#             */
/*   Updated: 2024/01/06 19:48:26 by jaechoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	read_more(t_file *fl, t_tmps *v, char *buf, t_list *node)
{
	ssize_t	rbyte;
	char	*str;

	while (!node || get_idx_nl(node->content, rbyte) == (size_t) rbyte)
	{
		rbyte = read(fl->fd, buf, BUFFER_SIZE);
		if (rbyte == -1)
			return (0);
		if (!rbyte)
			break ;
		str = malloc(rbyte * sizeof(char));
		if (!str)
			return (0);
		ft_memcpy_s(str, buf, rbyte);
		node = append_node(&v->lst_read, node, new_node(str, STR_NODE));
		if (!node)
			return (0);
		v->cnt_node++;
		v->len_last = rbyte;
	}
	if (v->cnt_node)
		v->last = node->content;
	return (1);
}

static void	build_str(t_file *fl, t_tmps *v, t_list *node)
{
	size_t	len;

	len = v->len_end;
	if (v->cnt_node)
		len += fl->len_save + (v->cnt_node - 1) * BUFFER_SIZE;
	v->result = malloc(len + 1);
	if (!v->result)
		return ;
	if (v->cnt_node)
	{
		ft_memcpy_s(v->result, fl->save, fl->len_save);
		v->result += fl->len_save;
		while (v->cnt_node-- > 1)
		{
			ft_memcpy_s(v->result, node->content, BUFFER_SIZE);
			v->result += BUFFER_SIZE;
			node = node->next;
		}
	}
	ft_memcpy_s(v->result, v->last, v->len_end);
	v->result += v->len_end;
	*v->result = 0;
	v->result -= len;
}

static void	get_line(t_file *fl, t_tmps *v)
{
	size_t	idx_nl;
	char	*buf;

	idx_nl = get_idx_nl(v->last, v->len_last);
	if (idx_nl >= v->len_last)
	{
		buf = malloc(BUFFER_SIZE * sizeof(char));
		if (!buf || !read_more(fl, v, buf, NULL))
		{
			free(buf);
			return ;
		}
		free(buf);
		if (!fl->len_save && !v->cnt_node)
			return ;
		idx_nl = get_idx_nl(v->last, v->len_last);
	}
	v->len_end = idx_nl + 1;
	if (idx_nl == v->len_last)
		v->len_end = v->len_last;
	build_str(fl, v, v->lst_read);
}

static void	reset_save(t_list **flst, t_file *fl, t_tmps *v)
{
	t_list	*temp;
	char	*lastsave;

	lastsave = fl->save;
	fl->len_save = v->len_last - v->len_end;
	fl->save = malloc(fl->len_save);
	if (!fl->save)
	{
		free(v->result);
		v->result = NULL;
	}
	if (!v->result)
		remove_fnode(flst, fl->fd);
	else
		ft_memcpy_s(fl->save, v->last + v->len_end, fl->len_save);
	free(lastsave);
	while (v->lst_read)
	{
		temp = v->lst_read;
		v->lst_read = v->lst_read->next;
		free(temp->content);
		free(temp);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*flst;
	t_list			*fnode;
	t_file			*fl;
	t_tmps			v;

	if (read(fd, NULL, 0) == -1)
	{
		remove_fnode(&flst, fd);
		return (NULL);
	}
	fnode = flst;
	if (fnode)
		while (((t_file *) fnode->content)->fd != fd && fnode->next)
			fnode = fnode->next;
	if (!fnode || ((t_file *) fnode->content)->fd != fd)
		fnode = append_node(&flst, fnode, new_node(&fd, FILE_NODE));
	if (!fnode)
		return (NULL);
	fl = fnode->content;
	v = (t_tmps){fl->save, fl->len_save, 0, NULL, 0, NULL};
	get_line(fnode->content, &v);
	reset_save(&flst, fnode->content, &v);
	return (v.result);
}
