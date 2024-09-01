/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 18:35:21 by aymohamm          #+#    #+#             */
/*   Updated: 2024/09/01 01:59:41 by inkahar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_builtin(t_prompt *prompt, t_str *n, int l, t_list *cmd)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!check_builtins(n) && n->full_cmd)
		execve(n->full_path, n->full_cmd, prompt->env);
	else if (n->full_cmd && !ft_strncmp(*n->full_cmd, "pwd", l) \
		&& l == 3)
		g_sig = cmd_pwd();
	else if (check_builtins(n) && n->full_cmd && \
		!ft_strncmp(*n->full_cmd, "echo", l) && l == 4)
		g_sig = cmd_echo(cmd);
	else if (check_builtins(n) && n->full_cmd && \
		!ft_strncmp(*n->full_cmd, "env", l) && l == 3)
	{
		m_put(prompt->env, 1, 1);
		g_sig = 0;
	}
}
static void	*redirect(t_list *command, int pipes[2])
{
	t_str	*node;

	node = command->content;
	if (node->infile != STDIN_FILENO)
	{
		if (dup2(node->infile, STDIN_FILENO) == -1)
			return (errno(ERR_DUP, NULL, 1));
		close(node->infile);
	}
	if (node->outfile != STDOUT_FILENO)
	{
		if (dup2(node->outfile, STDOUT_FILENO) == -1)
			return (errno(ERR_DUP, NULL, 1));
		close(node->outfile);
	}
	else if (command->next && dup2(pipes[WRITE_END], STDOUT_FILENO) == -1)
		return (errno(ERR_DUP, NULL, 1));
	close(pipes[WRITE_END]);
	return ("");
}


void	*handle_child(t_prompt *prompt, t_list *cmd, int fd[2])
{
	t_str	*info;
	int		l;

	info = cmd->content;
	l = 0;
	if (info->full_cmd)
		l = ft_strlen(*info->full_cmd);
	redirect(cmd, fd);
	close(fd[READ_END]);
	child_builtin(prompt, info, l, cmd);
	ft_lstclear(&prompt->cmds, free_content);
	exit(g_sig);
}


void exec_child(t_prompt *prompt, t_list *command, int fds[2])
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		close(fds[READ_END]);
		close(fds[WRITE_END]);
		errno(ERR_FORK, NULL, 1);
	}
	else if (!pid)
		handle_child(prompt, command, fds);
}

void	*check_exec(t_prompt *prompt, t_list *cmd, int fd[2])
{
	t_str	*info;
	DIR		*dir;

	info = cmd->content;
	dir = NULL;
	if (info->full_cmd)
		dir = opendir(*info->full_cmd);
	if (info->infile == -1 || info->outfile == -1)
		return (NULL);
	if ((info->full_path && access(info->full_path, X_OK) == 0) || check_builtins(info))
		exec_child(prompt, cmd, fd);
	else if (!check_builtins(info) && ((info->full_path && !access(info->full_path, F_OK)) || dir))
		g_sig = 126;
	else if (!check_builtins(info) && info->full_cmd)
		g_sig = 127;
	if (dir)
		closedir(dir);
	return ("");
}
