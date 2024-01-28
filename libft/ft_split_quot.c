/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaechoe <jaechoe@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:54:50 by jaechoe           #+#    #+#             */
/*   Updated: 2024/01/23 20:53:10 by jaechoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static void	search_quot(const char *s, char delim, t_quoted_str *qstr)
{
	while (*s != delim && !ft_strchr("\'\"", *s))
		s++;
	if (!*s || *s == delim)
	{
		qstr->end = s;
		return ;
	}
	qstr->start_quot = s;
	while (*++s && *s != *qstr->start_quot)
		;
	if (!*s)
	{
		qstr->start_quot = NULL;
		qstr->end = s;
		return ;
	}
	qstr->end_quot = s;
	while (*++s && *s != delim)
		;
	qstr->end = s;
	return ;
}

static const char	*append_qstr(
	const char *s, char delim, t_list **lst, size_t *cnt)
{
	t_quoted_str	*qstr;
	t_list			*newnode;

	qstr = malloc(sizeof(t_quoted_str));
	if (!qstr)
		return (NULL);
	qstr->start = s;
	qstr->start_quot = NULL;
	search_quot(s, delim, qstr);
	newnode = ft_lstnew(qstr);
	if (!newnode)
	{
		free(qstr);
		return (NULL);
	}
	ft_lstadd_back(lst, newnode);
	*cnt += 1;
	return (qstr->end);
}

static void	cp_quoted_str(char *dst, t_quoted_str *qstr)
{
	size_t	len1;
	size_t	len2;
	size_t	len3;

	if (qstr->start_quot)
	{
		len1 = qstr->start_quot - qstr->start;
		len2 = qstr->end_quot - qstr->start_quot - 1;
		len3 = qstr->end - qstr->end_quot - 1;
		if (len1)
			dst = ft_memcpy(dst, qstr->start, len1) + len1;
		if (len2)
			dst = ft_memcpy(dst, qstr->start_quot + 1, len2) + len2;
		if (len3)
			dst = ft_memcpy(dst, qstr->end_quot + 1, len3) + len3;
	}
	else
	{
		len1 = qstr->end - qstr->start;
		dst = ft_memcpy(dst, qstr->start, len1) + len1;
	}
	*dst = '\0';
}

static char	**lst_to_arr(t_list *lst, size_t lstsize)
{
	char			**result;
	char			**ptr;
	t_quoted_str	*qstr;
	size_t			_strlen;

	result = malloc((lstsize + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	ptr = result;
	while (lst)
	{
		qstr = lst->content;
		_strlen = qstr->end - qstr->start;
		if (qstr->start_quot)
			_strlen -= 2;
		*ptr = malloc(_strlen + 1);
		if (!*ptr)
			return (free2d(result, ptr - result));
		cp_quoted_str(*ptr, qstr);
		lst = lst->next;
		ptr++;
	}
	*ptr = NULL;
	return (result);
}

char	**ft_split_quot(const char *s, char delim)
{
	char	**result;
	t_list	*lst;
	size_t	cnt;

	lst = NULL;
	cnt = 0;
	while (*s)
	{
		while (*s == delim)
			s++;
		if (*s)
		{
			s = append_qstr(s, delim, &lst, &cnt);
			if (!s)
			{
				ft_lstclear(&lst, free);
				return (NULL);
			}
		}
	}
	result = lst_to_arr(lst, cnt);
	ft_lstclear(&lst, free);
	return (result);
}
