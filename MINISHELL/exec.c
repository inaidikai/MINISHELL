/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 22:43:25 by aymohamm          #+#    #+#             */
/*   Updated: 2024/09/05 16:35:24 by inkahar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_command(char **env_path, char *cmd, char *full_path)
{
	char	*temp;
	int		i;

	i = -1;
	full_path = NULL;
	while (env_path && env_path[++i])
	{
		free(full_path);
		temp = ft_strjoin(env_path[i], "/");
		if (!temp)
			return (NULL);
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (!full_path)
			return (NULL);
		if (access(full_path, F_OK) == 0)
			break ;
	}
	if (!env_path || !env_path[i])
	{
		free(full_path);
		return (NULL);
	}
	return (full_path);
}

static DIR	*check_cmd(t_prompt *prompt, t_list *cmd, char ***s, char *path)
{
	t_str	*n;
	DIR		*dir;

	dir = NULL;
	n = cmd->content;
	if (n && n->full_cmd)
		dir = opendir(*n->full_cmd);
	if (n && n->full_cmd && ft_strchr(*n->full_cmd, '/') && !dir)
	{
		*s = ft_split(*n->full_cmd, '/');
		n->full_path = ft_strdup(*n->full_cmd);
		free(n->full_cmd[0]);
		n->full_cmd[0] = ft_strdup(s[0][m_size(*s) - 1]);
	}
	else if (!check_builtins(n) && n && n->full_cmd && !dir)
	{
		path = mini_getenv("PATH", prompt->env, 4);
		*s = ft_split(path, ':');
		free(path);
		n->full_path = find_command(*s, *n->full_cmd, n->full_path);
		if (!n->full_path || !n->full_cmd[0] || !n->full_cmd[0][0])
			errno(NO_CMD, *n->full_cmd, 127);
	}
	return (dir);
}

void	get_cmd(t_prompt *prompt, t_list *cmd, char **s, char *path)
{
	t_str	*n;
	DIR		*dir;

	n = cmd->content;
	dir = check_cmd(prompt, cmd, &s, path);
	if (!check_builtins(n) && n && n->full_cmd && dir)
		errno(CHECK_DIR, *n->full_cmd, 126);
	else if (!check_builtins(n) && n && n->full_path && \
		access(n->full_path, F_OK) == -1)
		errno(NOTDIR, n->full_path, 127);
	else if (!check_builtins(n) && n && n->full_path && \
		access(n->full_path, X_OK) == -1)
		errno(NPERM, n->full_path, 126);
	if (dir)
		closedir(dir);
	m_free(&s);
}

void	*exec_cmd(t_prompt *prompt, t_list *cmd)
{
	int		fd[2];

	get_cmd(prompt, cmd, NULL, NULL);
	if (pipe(fd) == -1)
		return (errno(ERR_PIPE, NULL, 1));
	if (!check_exec(prompt, cmd, fd))
		return (NULL);
	close(fd[WRITE_END]);
	if (cmd->next && !((t_str *)cmd->next->content)->infile)
		((t_str *)cmd->next->content)->infile = fd[READ_END];
	else
		close(fd[READ_END]);
	if (((t_str *)cmd->content)->infile > 2)
		close(((t_str *)cmd->content)->infile);
	if (((t_str *)cmd->content)->outfile > 2)
		close(((t_str *)cmd->content)->outfile);
	return (NULL);
}
