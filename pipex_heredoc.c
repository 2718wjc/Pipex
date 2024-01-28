/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaechoe <jaechoe@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:52:30 by jaechoe           #+#    #+#             */
/*   Updated: 2024/01/27 21:14:01 by jaechoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/GNL/get_next_line.h"

static t_bool	hdoc_interface(t_vars_hdoc *v_h)
{
	write(1, "> ", 2);
	v_h->line = get_next_line(0);
	if (!v_h->line)
		err_handle("error", "get_next_line()", 1);
	if (!ft_strncmp(v_h->lmt, v_h->line, v_h->len_lmt)
		&& v_h->line[v_h->len_lmt] == '\n')
	{
		free(v_h->line);
		return (FALSE);
	}
	v_h->len_curr = ft_strlen(v_h->line);
	return (TRUE);
}

static void	_transfer(t_vars_hdoc *v_h, int *pfd, int fd)
{
	char	buf[PIPESIZE];

	close(pfd[1]);
	read(pfd[0], buf, v_h->len_tot);
	close(pfd[0]);
	write(fd, buf, v_h->len_tot);
	write(fd, v_h->line, v_h->len_curr);
}

static int	gen_tmpfile(
	const char *tmpnam, t_vars_hdoc *v_h, int *pfd)
{
	int		fd;

	fd = open(tmpnam, O_WRONLY | O_EXCL | O_CREAT, 0600);
	if (fd == -1)
		err_handle("Error creating temp file for heredoc", NULL, 1);
	if (pfd)
		_transfer(v_h, pfd, fd);
	while (TRUE)
	{
		if (!hdoc_interface(v_h))
		{
			close(fd);
			fd = open(tmpnam, O_RDONLY);
			if (fd == -1)
				err_handle("Error creating temp file for heredoc", NULL, 1);
			return (fd);
		}
		write(fd, v_h->line, v_h->len_curr);
		free(v_h->line);
	}
}

int	get_heredoc(const char *lmt, const char *tmpnam)
{
	t_vars_hdoc	v_h;
	int			pfd[2];

	v_h = (t_vars_hdoc){NULL, 0, 0, lmt, ft_strlen(lmt)};
	if (pipe(pfd) == -1)
		return (gen_tmpfile(tmpnam, &v_h, NULL));
	while (TRUE)
	{
		if (!hdoc_interface(&v_h))
		{
			close(pfd[1]);
			return (pfd[0]);
		}
		if (v_h.len_tot + v_h.len_curr > PIPESIZE)
			return (gen_tmpfile(tmpnam, &v_h, pfd));
		write(pfd[1], v_h.line, v_h.len_curr);
		free(v_h.line);
		v_h.len_tot += v_h.len_curr;
	}
}
