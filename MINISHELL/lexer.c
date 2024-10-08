/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 14:29:25 by aymohamm          #+#    #+#             */
/*   Updated: 2024/09/04 20:14:43 by inkahar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_count_words(const char *s, char *c, int i[2])
{
	int		q[2];

	q[0] = 0;
	q[1] = 0;
	while (s[i[0]] != '\0')
	{
		if (!ft_strchr(c, s[i[0]]))
		{
			i[1]++;
			while ((!ft_strchr(c, s[i[0]]) || q[0]) && s[i[0]] != '\0')
			{
				if (!q[1] && (s[i[0]] == '\"' || s[i[0]] == '\''))
					q[1] = s[i[0]];
				q[0] = (q[0] + (s[i[0]] == q[1])) % 2;
				q[1] *= q[0] != 0;
				i[0]++;
			}
			if (q[0])
				return (-1);
		}
		else
			i[0]++;
	}
	return (i[1]);
}

static char	**ft_fill_array(char **store, char const *s, char *set, int i[3])
{
	int	s_len;
	int	q[2];

	q[0] = 0;
	q[1] = 0;
	s_len = ft_strlen(s);
	while (s[i[0]])
	{
		while (ft_strchr(set, s[i[0]]) && s[i[0]] != '\0')
			i[0]++;
		i[1] = i[0];
		while ((!ft_strchr(set, s[i[0]]) || q[0] || q[1]) && s[i[0]])
		{
			q[0] = (q[0] + (!q[1] && s[i[0]] == '\'')) % 2;
			q[1] = (q[1] + (!q[0] && s[i[0]] == '\"')) % 2;
			i[0]++;
		}
		if (i[1] >= s_len)
			store[i[2]++] = "\0";
		else
			store[i[2]++] = ft_substr(s, i[1], i[0] - i[1]);
	}
	return (store);
}

static char	**ft_cmdtrim(char const *s, char *set)
{
	char	**store;
	int		nwords;
	int		i[3];
	int		counts[2];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	counts[0] = 0;
	counts[1] = 0;
	if (!s)
		return (NULL);
	nwords = ft_count_words(s, set, counts);
	if (nwords == -1)
		return (NULL);
	store = malloc((nwords + 1) * sizeof(char *));
	if (store == NULL)
		return (NULL);
	store = ft_fill_array(store, s, set, i);
	store[nwords] = NULL;
	return (store);
}

void	*lexer(char *store, t_prompt *p)
{
	char	**trimmed_args;
	t_str	*list;

	if (!store)
	{
		printf("exit\n");
		return (NULL);
	}
	if (store[0] != '\0')
		add_history(store);
	trimmed_args = ft_cmdtrim(store, " ");
	free(store);
	if (!trimmed_args)
		errno(UNCLOSEDPARA, NULL, 1);
	if (!trimmed_args)
		return ("");
	p = parsing(trimmed_args, p);
	if (p && p->cmds)
		list = p->cmds->content;
	if (p && p->cmds && list && list->full_cmd && ft_lstsize(p->cmds) == 1)
		p->env = mini_setenv("_", list->full_cmd[m_size(list->full_cmd) - 1],
				p->env, 1);
	if (p && p->cmds)
		ft_lstclear(&p->cmds, free_content);
	return (p);
}
