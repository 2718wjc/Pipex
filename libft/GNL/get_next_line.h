/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaechoe <jaechoe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 17:07:09 by jaechoe           #+#    #+#             */
/*   Updated: 2024/01/06 19:50:58 by jaechoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include <unistd.h>
# include <stdlib.h>
# include "../libft.h"

# define FILE_NODE 1
# define STR_NODE 0

typedef int	t_type;

typedef struct s_file
{
	int		fd;
	char	*save;
	size_t	len_save;
}	t_file;

typedef struct s_tmps
{
	char	*last;
	size_t	len_last;
	size_t	len_end;
	t_list	*lst_read;
	size_t	cnt_node;
	char	*result;
}	t_tmps;

char	*get_next_line(int fd);
t_list	*new_node(void *content, t_type type);
t_list	*append_node(t_list **lst, t_list *lastnode, t_list *new);
size_t	get_idx_nl(const char *s, size_t len);
void	*ft_memcpy_s(void *dst, const void *src, size_t n);
void	remove_fnode(t_list **flst, int fd);

#endif
