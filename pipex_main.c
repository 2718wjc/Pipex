/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaechoe <jaechoe@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 18:12:45 by jaechoe           #+#    #+#             */
/*   Updated: 2024/03/02 18:12:50 by jaechoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include "pipex.h"

static char	**get_path(char **envp)
{
	char	**path;
	char	*temp;
	int		i;

	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5))
			continue ;
		path = ft_split(envp[i], ':');
		if (!path)
			return (NULL);
		temp = path[0];
		path[0] = ft_strdup_s(path[0] + 5);
		free(temp);
		return (path);
	}
	path = malloc(sizeof(char *));
	while (!path)
		path = malloc(sizeof(char *));
	*path = NULL;
	return (path);
}

static void	init_vars(t_vars_pipex *v, int argc, char **argv, char **envp)
{
	v->argv = argv;
	v->envp = envp;
	v->path = get_path(envp);
	if (!v->path)
		err_handle(NULL, NULL, 1);
	if (!ft_strncmp(argv[1], "here_doc", 9))
	{
		v->offset = 3;
		v->tmpnam = gen_tmpnam("/tmp/pipex_tmp");
		v->heredoc_fd = get_heredoc(argv[2], v->tmpnam);
	}
	else
	{
		v->offset = 2;
		v->tmpnam = NULL;
	}
	v->n_cmd = argc - v->offset - 1;
	v->pid = malloc(v->n_cmd * sizeof(pid_t));
	if (!v->pid)
		err_handle(NULL, NULL, 1);
}

static void	run_cmd(t_vars_pipex *v, int i, int *fd)
{
	char	**cmd;
	char	*exefile;

	close(fd[0]);
	if (i == 0)
		fd[0] = get_infile(v);
	else
		fd[0] = fd[2];
	if (i == v->n_cmd - 1)
	{
		close(fd[1]);
		fd[1] = set_outfile(v);
	}
	if (dup2(fd[0], 0) == -1)
		err_handle(NULL, NULL, -1);
	if (dup2(fd[1], 1) == -1)
		err_handle(NULL, NULL, -1);
	close(fd[0]);
	close(fd[1]);
	cmd = get_cmd(v->argv[v->offset + i], v->path, &exefile);
	if (execve(exefile, cmd, v->envp) == -1)
		err_handle(NULL, NULL, 1);
}

/*
 * fd[0]: read-end
 * fd[1]: write-end
 * fd[2]: read-end 인 fd[0]을 임시로 저장해두는 용도.
 * 다음 회차 때 fd[0]에는 새로운 read-end 가 저장되는데,
 * 그 때 fd[2]에는 이전 read-end 가 담겨있기 때문에
 * 분기 후 자식프로세스가 그곳을 통해 이전 자식프로세스의 데이터를 받을 수 있게 된다.
 */
static void	start_proc(t_vars_pipex *v)
{
	int	fd[3];
	int	i;

	fd[2] = -1;
	i = 0;
	while (i < v->n_cmd)
	{
		if (pipe(fd) == -1)
			err_handle(NULL, NULL, -1);
		v->pid[i] = fork();
		if (v->pid[i] < 0)
			err_handle(NULL, NULL, -1);
		else if (v->pid[i] > 0)
		{
			close(fd[2]);
			close(fd[1]);
			fd[2] = fd[0];
		}
		else
			run_cmd(v, i, fd);
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_vars_pipex	v;
	int				i;
	int				stat;

	if (argc < 5)
		err_handle("Too few arguments", NULL, 1);
	init_vars(&v, argc, argv, envp);
	start_proc(&v);
	i = 0;
	while (i < v.n_cmd)
	{
		waitpid(v.pid[i], &stat, 0);
		i++;
	}
	unlink(v.tmpnam);
	return (WEXITSTATUS(stat));
}
