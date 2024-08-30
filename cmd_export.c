/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymohamm <aymohamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 13:10:22 by aymohamm          #+#    #+#             */
/*   Updated: 2024/08/24 13:25:28 by aymohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find(char *av, char **env, int ac[2])
{
	int	pos;

	ac[1] = 0;
	pos = ft_strchr_i(av, '=');
	if (pos == -1)
		return (-1);
	while (env[ac[1]])
	{
		if (!ft_strncmp(env[ac[1]], av, pos + 1))
			return (1);
		ac[1]++;
	}
	return (0);
}

int	cmd_export(t_prompt *prompt)
{
	int		ac[2];
	int		pos;
	char	**av;

	av = ((t_str *)prompt->cmds->content)->full_cmd;
	if (m_size(av) >= 2)
	{
		ac[0] = 1;
		while (av[ac[0]])
		{
			pos = find(av[ac[0]], prompt->env, ac);
			if (pos == 1)
			{
				free(prompt->env[ac[1]]);
				prompt->env[ac[1]] = ft_strdup(av[ac[0]]);
			}
			else if (!pos)
				prompt->env = m_exdup(prompt->env, av[ac[0]]);
			ac[0]++;
		}
	}
	return (0);
}

int	cmd_unset(t_prompt *prompt)
{
	char	**av;
	char	*store;
	int		ac[2];

	ac[0] = 1;
	av = ((t_str *)prompt->cmds->content)->full_cmd;
	if (m_size(av) >= 2)
	{
		while (av[ac[0]])
		{
			if (av[ac[0]][ft_strlen(av[ac[0]]) - 1] != '=')
			{
				store = ft_strjoin(av[ac[0]], "=");
				free(av[ac[0]]);
				av[ac[0]] = store;
			}
			if (find(av[ac[0]], prompt->env, ac))
				m_replace(&prompt->env, NULL, ac[1]);
		}
	}
	return (0);
}
