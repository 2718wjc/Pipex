/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaechoe <jaechoe@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 18:13:42 by jaechoe           #+#    #+#             */
/*   Updated: 2024/03/02 18:13:48 by jaechoe          ###   ########.fr       */
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

int	get_infile(t_vars_pipex *v)
{
	int	fd;

	if (v->offset == 2)
	{
		fd = open(v->argv[1], O_RDONLY);
		if (fd == -1)
			err_handle(NULL, v->argv[1], 1);
	}
	else
		fd = v->heredoc_fd;
	return (fd);
}

int	set_outfile(t_vars_pipex *v)
{
	int	fd;

	if (v->offset == 2)
		fd = open(v->argv[v->offset + v->n_cmd],
				O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else
		fd = open(v->argv[v->offset + v->n_cmd],
				O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
		err_handle(NULL, v->argv[v->offset + v->n_cmd], 1);
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
		if (access(exefile, F_OK) == 0)
		{
			if (access(exefile, X_OK) == 0)
				return (exefile);
			else
				err_handle(NULL, cmd, 126);
		}
		free(exefile);
	}
	err_handle("command not found", cmd, 127);
	return (NULL);
}

char	**get_cmd(char *cmdstr, char **path, char **exefile)
{
	char	**cmd;

	cmd = ft_split_quot(cmdstr, ' ');
	if (!cmd)
		err_handle(NULL, NULL, 1);
	if (!ft_strchr(cmd[0], '/'))
	{
		*exefile = check_path(cmd[0], path);
		return (cmd);
	}
	if (access(cmd[0], F_OK) == -1)
		err_handle(NULL, cmd[0], 127);
	if (access(cmd[0], X_OK) == -1)
		err_handle(NULL, cmd[0], 126);
	*exefile = cmd[0];
	return (cmd);
}
