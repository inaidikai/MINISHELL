/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymohamm <aymohamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 22:43:25 by aymohamm          #+#    #+#             */
/*   Updated: 2024/08/25 17:27:25 by aymohamm         ###   ########.fr       */
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

static DIR	*try_open_dir(char *cmd)
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
		n->full_cmd[0] = ft_strdup(splits[0][ft_matrixlen(*splits) - 1]);
	}
}

static DIR	*check_cmd(t_prompt *prompt, t_list *cmd, char ***splits, char *path)
{
	t_str	*n = cmd->content;
	DIR		*dir = try_open_dir(*n->full_cmd);

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
			mini_perror(NCMD, *n->full_cmd, 127);
	}
	return (dir);
}

void	handle_cmd(t_prompt *prompt, t_list *cmd, char **paths, char *path)
{
	t_str	*info;
	DIR		*dir;

	info = cmd->content;
	dir = check_dir(info);
	if (!is_builtin(info))
	{
		if (dir)
		{
			dir_error(info);
		}
		else
		{
			path = mini_getenv("PATH", prompt->env, 4);
			*paths = ft_split(path, ':');
			free(path);
			info->full_path = find_cmd(*paths, *info->full_cmd, info->full_path);
			path_errors(info);
		}
	}
	if (dir)
		closedir(dir);
	ft_free_matrix(paths);
}

static DIR *check_dir(t_str *info)
{
	if (info && info->full_cmd)
		return opendir(*info->full_cmd);
	return NULL;
}

static void dir_error(t_str *info)
{
	if (info && info->full_cmd)
		mini_perror(IS_DIR, *info->full_cmd, 126);
}

static void path_errors(t_str *info)
{
	if (info && info->full_path)
	{
		if (access(info->full_path, F_OK) == -1)
			mini_perror(NDIR, info->full_path, 127);
		else if (access(info->full_path, X_OK) == -1)
			mini_perror(NPERM, info->full_path, 126);
	}
}


void *exec(t_prompt *prompt, t_list *cmd)
{
    int file[2];

    handle_cmd(prompt, cmd,NULL, NULL);
    //CHECK

}