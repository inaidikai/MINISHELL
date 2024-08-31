/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 22:43:25 by aymohamm          #+#    #+#             */
/*   Updated: 2024/08/31 15:05:02 by inkahar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*con_cmdpath(char *path, char *cmd)
{
	char	*t;
	char	*full_path;

	t = ft_strjoin(path, "/");
	if (!t)
		return (NULL);
	full_path = ft_strjoin(t, cmd);
	free(t);
	return (full_path);
}
// static DIR *check_dir(t_str *info)
// {
// 	if (info && info->full_cmd)
// 		return opendir(*info->full_cmd);
// 	return NULL;
// }

// static void dir_error(t_str *info)
// {
// 	if (info && info->full_cmd)
// 		errno(CHECK_DIR, *info->full_cmd, 126);
// }
static char	*find_cmd(char **e_path, char *cmd, char *full_path)
{
	int		i;

	full_path = NULL;
	i = 0;
	while (e_path && e_path[i])
	{
		free(full_path);
		full_path = con_cmdpath(e_path[i], cmd);
		if (!full_path)
			return (NULL);
		if (access(full_path, F_OK) == 0)
			break ;
		i++;
	}
	if (!e_path || !e_path[i])
	{
		free(full_path);
		return (NULL);
	}
	return (full_path);
}

static DIR	*dir_open(char *cmd)
{
	if (cmd)
		return (opendir(cmd));
	return (NULL);
}

static void	handle_full_cmd(t_str *n, char ***splits)
{
	*splits = ft_split(*n->full_cmd, '/');
	n->full_path = ft_strdup(*n->full_cmd);
	if (n->full_cmd[0])
	{
		free(n->full_cmd[0]);
		n->full_cmd[0] = ft_strdup(splits[0][m_size(*splits) - 1]);
	}
}

static DIR	*check_cmd(t_prompt *prompt, t_list *cmd, char ***splits, char *path)
{
	t_str	*n = cmd->content;
	DIR		*dir = dir_open(*n->full_cmd);

	if (n && n->full_cmd && ft_strchr(*n->full_cmd, '/') && !dir)
		handle_full_cmd(n, splits);
	else if (!check_builtins(n) && n && n->full_cmd && !dir)
	{
		if ((path = mini_getenv("PATH", prompt->env, 4)))
		{
			*splits = ft_split(path, ':');
			free(path);
			n->full_path = find_cmd(*splits, *n->full_cmd, n->full_path);
		}
		if (!n->full_path || !n->full_cmd[0] || !n->full_cmd[0][0])
			errno(NO_CMD, *n->full_cmd, 127);
	}
	return (dir);
}
// static void path_errors(t_str *info)
// {
// 	if (info && info->full_path)
// 	{
// 		if (access(info->full_path, F_OK) == -1)
// 			errno(NDIR, info->full_path, 127);
// 		else if (access(info->full_path, X_OK) == -1)
// 			errno(NPERM, info->full_path, 126);
// 	}
// }
// void	handle_cmd(t_prompt *prompt, t_list *cmd, char **paths, char *path)
// {
// 	t_str	*info;
// 	DIR		*dir;

// 	info = cmd->content;
// 	dir = check_dir(info);
// 	if (!check_builtins(info))
// 	{
// 		if (dir)
// 		{
// 			dir_error(info);
// 		}
// 		else
// 		{
// 			path = mini_getenv("PATH", prompt->env, 4);
// 			paths = ft_split(path, ':');
// 			free(path);
// 			info->full_path = find_cmd(paths, *info->full_cmd, info->full_path);
// 			path_errors(info);
// 		}
// 	}
// 	if (dir)
// 		closedir(dir);
// 	m_free(&paths);
// }






static void set_redir(t_list *cmd, int fd[2])
{
    if (cmd->next && !((t_str *)cmd->next->content)->infile)
        ((t_str *)cmd->next->content)->infile = fd[READ_END];
    else
        close(fd[READ_END]);
}

static void close_files(t_list *cmd)
{
    if (((t_str *)cmd->content)->infile > 2)
        close(((t_str *)cmd->content)->infile);
    if (((t_str *)cmd->content)->outfile > 2)
        close(((t_str *)cmd->content)->outfile);
}
 
void *exec_cmd(t_prompt *prompt, t_list *cmd_list)
{
    int fd[2];

    check_cmd(prompt, cmd_list, NULL, NULL);
    if (pipe(fd) == -1)
        return (errno(ERR_PIPE, NULL, 1));
    if (!check_exec(prompt, cmd_list, fd))
        return (NULL);
    close(fd[WRITE_END]);
    set_redir(cmd_list, fd);
    close_files(cmd_list);
    return (NULL);
}
