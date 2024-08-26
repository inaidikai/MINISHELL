/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymohamm <aymohamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 18:35:21 by aymohamm          #+#    #+#             */
/*   Updated: 2024/08/26 08:15:18 by aymohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute_command(t_prompt *env, t_str *cmd_info)
{
	if (!is_builtin(cmd_info) && cmd_info->full_cmd)
	{
		execve(cmd_info->full_path, cmd_info->full_cmd, env->env);
		return -1;
	}
	return 0;
}

int handle_builtin_commands(t_prompt *p, t_str *cmd_info, int cmd_len, t_list *cmd_list)
{
	if (cmd_info->full_cmd && cmd_len == 3 && !ft_strncmp(*cmd_info->full_cmd, "pwd", cmd_len))
	{
		return cmd_pwd();
	}
	else if (is_builtin(cmd_info) && cmd_info->full_cmd && cmd_len == 4 && !ft_strncmp(*cmd_info->full_cmd, "echo", cmd_len))
	{
		return cmd_echo(cmd_list);
	}
	else if (is_builtin(cmd_info) && cmd_info->full_cmd && cmd_len == 3 && !ft_strncmp(*cmd_info->full_cmd, "env", cmd_len))
	{
		m_put(p->env, 1, 1);
		return 0;
	}
	return -1;
}

void process_builtin(t_prompt *env, t_str *cmd_info, int cmd_len, t_list *cmd_list)
{
	reset_signals_to_default();

	if (execute_command(env, cmd_info) == 0)
	{
		int status = handle_builtin_commands(env, cmd_info, cmd_len, cmd_list);
		if (status != -1)
		{
			g_sig = status;
		}
	}
}

static void	*redirect(t_list *command, int pipes[2])
{
	t_str	*info = command->content;

	if (info->infile != STDIN_FILENO)
	{
		if (dup2(info->infile, STDIN_FILENO) == -1)
			return (errno(ERR_DUP, NULL, 1));
		close(info->infile);
	}

	if (info->outfile != STDOUT_FILENO)
	{
		if (dup2(info->outfile, STDOUT_FILENO) == -1)
			return (errno(ERR_DUP, NULL, 1));
		close(info->outfile);
	}
	else if (command->next)
	{
		if (dup2(pipes[WRITE_END], STDOUT_FILENO) == -1)
			return (errno(ERR_DUP, NULL, 1));
	}

	close(pipes[WRITE_END]);
	return "";
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
	process_builtin(prompt, info, l, cmd);
	ft_lstclear(&prompt->cmds, free_content);
	exit(g_sig);
}

void exec_child(t_prompt *prompt, t_list *command, int fds[2])
{
    pid_t child_pid;

    if ((child_pid = fork()) == 0)
    {
        handle_child(prompt, command, fds);
    }
    else if (child_pid < 0)
    {
        close(fds[READ_END]);
        close(fds[WRITE_END]);
        errno(ERR_FORK, NULL, 1);
    }
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
	if ((info->full_path && access(info->full_path, X_OK) == 0) || is_builtin(info))
		exec_child(prompt, cmd, fd);
	else if (!is_builtin(info) && ((info->full_path && !access(info->full_path, F_OK)) || dir))
		g_sig = 126;
	else if (!is_builtin(info) && info->full_cmd)
		g_sig = 127;
	if (dir)
		closedir(dir);
	return ("");
}
