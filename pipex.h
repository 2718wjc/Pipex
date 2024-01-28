/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaechoe <jaechoe@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 22:07:24 by jaechoe           #+#    #+#             */
/*   Updated: 2024/01/27 22:00:29 by jaechoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/errno.h>
# include "libft/libft.h"

# define PIPESIZE 1024

typedef struct s_vars_pipex
{
	char	**argv;
	char	**envp;
	char	**path;
	int		offset;
	int		heredoc_fd;
	char	*tmpnam;
	int		n_cmd;
	pid_t	*pid;
	int		*pipe_r;
}	t_vars_pipex;

typedef struct s_vars_hdoc
{
	char		*line;
	size_t		len_curr;
	size_t		len_tot;
	const char	*lmt;
	size_t		len_lmt;
}	t_vars_hdoc;

int		get_heredoc(const char *lmt, const char *tmpnam);
void	err_handle(char *errmsg, char *obj, int exitcode);
char	*gen_tmpnam(const char *basename);
int		get_iofile(t_vars_pipex *v, int i);
char	**get_cmd(char *cmdstr, char **path, char **exefile);

#endif
