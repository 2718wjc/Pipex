/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaechoe <jaechoe@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 22:10:47 by jaechoe           #+#    #+#             */
/*   Updated: 2024/01/27 21:28:07 by jaechoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "pipex.h"

void	err_handle(char *errmsg, char *obj, int exitcode)
{
	write(2, "pipex: ", 7);
	if (obj)
	{
		ft_putstr_fd(obj, 2);
		write(2, ": ", 2);
	}
	if (errmsg)
		ft_putstr_fd(errmsg, 2);
	else
		ft_putstr_fd(strerror(errno), 2);
	write(2, "\n", 1);
	if (exitcode > -1)
		exit(exitcode);
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

int	get_iofile(t_vars_pipex *v, int i)
{
	int	fd;

	fd = -1;
	if (i == 0 && v->offset == 2)
	{
		fd = open(v->argv[1], O_RDONLY);
		if (fd == -1)
			err_handle(NULL, v->argv[1], 1);
	}
	else if (i == 0 && v->offset == 3)
		fd = v->heredoc_fd;
	else if (i == v->n_cmd - 1)
	{
		if (v->offset == 2)
			fd = open(v->argv[v->offset + v->n_cmd],
					O_WRONLY | O_TRUNC | O_CREAT, 0644);
		else if (v->offset == 3)
			fd = open(v->argv[v->offset + v->n_cmd],
					O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (fd == -1)
			err_handle(NULL, v->argv[v->offset + v->n_cmd], 1);
	}
	return (fd);
}

static char	*check_path(char *cmd, char **path)
{
	char	*exefile;
	char	*temp;

	while (*path)
	{
		temp = ft_strjoin("/", cmd);
		exefile = ft_strjoin(*path++, temp);
		if (!temp || !exefile)
			err_handle(NULL, NULL, 1);
		free(temp);
		if (access(exefile, X_OK) == 0)
			return (exefile);
		free(exefile);
	}
	return (NULL);
}

char	**get_cmd(char *cmdstr, char **path, char **exefile)
{
	char	**cmd;

	cmd = ft_split_quot(cmdstr, ' ');
	if (!cmd)
		err_handle(NULL, NULL, 1);
	*exefile = check_path(cmd[0], path);
	if (*exefile)
		return (cmd);
	if (!ft_strchr(cmd[0], '/'))
		err_handle("command not found", cmd[0], 127);
	else if (access(cmd[0], F_OK) == -1)
		err_handle(NULL, cmd[0], 127);
	else if (access(cmd[0], X_OK) == -1)
		err_handle(NULL, cmd[0], 126);
	*exefile = cmd[0];
	return (cmd);
}
