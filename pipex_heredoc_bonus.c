/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_heredoc_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaechoe <jaechoe@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 18:11:06 by jaechoe           #+#    #+#             */
/*   Updated: 2024/03/02 18:11:18 by jaechoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
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

char	*gen_tmpnam(const char *basename)
{
	char	*filename;
	char	*suffix;
	int		i;

	filename = ft_strdup(basename);
	i = 0;
	while ((!filename || access(filename, F_OK) > -1) && ++i < 10000)
	{
		free(filename);
		suffix = ft_itoa(i);
		filename = ft_strjoin(basename, suffix);
		free(suffix);
	}
	if (i == 10000)
		err_handle("Cannot set tempfile name", NULL, 1);
	return (filename);
}

/*
 * 처음에는 파이프(가상파일)을 생성해서 입력내용을 저장하다가
 * 입력이 PIPE_SIZE 보다 커지면 tmpfile 을 직접 생성해서
 * 지금까지 파이프에 저장했던 것들을 모두 tmpfile 로 옮기고 파이프는 닫은 후,
 * 이후의 입력도 계속 tmpfile 에 저장하는 식으로 구현했다.
 * 파이프는 사이즈 제한이 있다. 여기서는 그냥 안전하게 1024byte 로 임의 설정해서 사용했는데,
 * 실제 사이즈는 시스템마다 다르겠지만 적어도 1024byte 보다는 크다.
 * 한편 tmpfile 을 직접 생성하는 경우에는 이후 적절히 삭제하는 과정이 필요하다.
 */
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
