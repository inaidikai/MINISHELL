/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymohamm <aymohamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 22:43:25 by aymohamm          #+#    #+#             */
/*   Updated: 2024/08/25 16:54:15 by aymohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*concat_cmd_path(char *path, char *cmd)
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
		full_path = concat_cmd_path(e_path[i], cmd);
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



void *exec(t_prompt *prompt, t_list *cmd)
{
    int file[2];

    //get cmd + dir check
}