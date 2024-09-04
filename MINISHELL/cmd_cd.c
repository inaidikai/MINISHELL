/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 17:03:19 by aymohamm          #+#    #+#             */
/*   Updated: 2024/09/04 19:52:21 by inkahar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_err(char **s[2])
{
	DIR	*dir;

	dir = NULL;
	if (s[0][1])
		dir = opendir(s[0][1]);
	if (!s[0][1] && s[1][0] && !s[1][0][0])
	{
		g_sig = 1;
		ft_putstr_fd("minishell: HOME not set\n", 2);
	}
	if (s[1][0] && !s[0][1])
		g_sig = chdir(s[1][0]) == -1;
	if (s[0][1] && dir && access(s[0][1], F_OK) != -1)
		chdir(s[0][1]);
	else if (s[0][1] && access(s[0][1], F_OK) == -1)
		errno(NOFILE_DIR, s[0][1], 1);
	else if (s[0][1])
		errno(NOTDIR, s[0][1], 1);
	if (s[0][1] && dir)
		closedir(dir);
}

int	cmd_cd(t_prompt *p)
{
	char	**s[2];
	char	*store;

	g_sig = 0;
	s[0] = ((t_str *)p->cmds->content)->full_cmd;
	store = mini_getenv("HOME", p->env, 4);
	if (!store)
		store = ft_strdup("");
	s[1] = m_exdup(NULL, store);
	free(store);
	store = getcwd(NULL, 0);
	s[1] = m_exdup(s[1], store);
	free(store);
	handle_err(s);
	if (!g_sig)
		p->env = mini_setenv("OLDPWD", s[1][1], p->env, 6);
	store = getcwd(NULL, 0);
	if (!store)
		store = ft_strdup("");
	s[1] = m_exdup(s[1], store);
	free(store);
	p->env = mini_setenv("PWD", s[1][2], p->env, 3);
	m_free(&s[1]);
	return (g_sig);
}
