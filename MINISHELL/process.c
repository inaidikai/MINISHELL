/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymohamm <aymohamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 18:35:21 by aymohamm          #+#    #+#             */
/*   Updated: 2024/08/25 20:09:07 by aymohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void execute_child(t_prompt *prompt, t_list *command, int fds[2])
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
        mini_perror(FORKERR, NULL, 1);
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
		exec_fork(prompt, cmd, fd);
	else if (!is_builtin(info) && ((info->full_path && !access(info->full_path, F_OK)) || dir))
		g_sig = 126;
	else if (!is_builtin(info) && info->full_cmd)
		g_sig = 127;
	if (dir)
		closedir(dir);
	return ("");
}
