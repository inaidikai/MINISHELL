/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillnode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 13:41:43 by inkahar           #+#    #+#             */
/*   Updated: 2024/09/01 01:52:21 by inkahar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

char	**m_dup(char **m)
{
	char	**out;
	int		n_rows;
	int		i;

	i = 0;
	n_rows = m_size(m);
	out = malloc(sizeof(char *) * (n_rows + 1));
	if (!out)
		return (NULL);
	while (m[i])
	{
		out[i] = ft_strdup(m[i]);
		if (!out[i])
		{
			m_free(&out);
			return (NULL);
		}
		i++;
	}
	out[i] = NULL;
	return (out);
}
static t_str	*get_params(t_str *node, char **a[2], int *i)
{
	if (a[0][*i])
	{
		if (a[0][*i][0] == '>' && a[0][*i + 1] && a[0][*i + 1][0] == '>')
			node = get_outfile2(node, a[1], i);
		else if (a[0][*i][0] == '>')
			node = get_outfile1(node, a[1], i);
		else if (a[0][*i][0] == '<' && a[0][*i + 1] && \
			a[0][*i + 1][0] == '<')
			node = get_infile2(node, a[1], i);
		else if (a[0][*i][0] == '<')
			node = get_infile1(node, a[1], i);
		else if (a[0][*i][0] != '|')
			node->full_cmd = m_exdup(node->full_cmd, a[1][*i]);
		else
		{
			errno(PIPENDERR, NULL, 2);
			*i = -2;
		}
		return (node);
	}
	errno(PIPENDERR, NULL, 2);
	*i = -2;
	return (node);
}
static char	**get_trimmed(char **args)
{
	char	**temp;
	char	*aux;
	int		j;

	j = -1;
	temp = m_dup(args);
	while (temp && temp[++j])
	{
		aux = clean_trim(temp[j], 0, 0);
		free(temp[j]);
		temp[j] = aux;
	}
	return (temp);
}

static t_list	*stop_fill(t_list *cmds, char **args, char **temp)
{
	ft_lstclear(&cmds, free_content);
	m_free(&temp);
	m_free(&args);
	return (NULL);
}
t_list	*fill_nodes(char **args, int i)
{
	t_list	*cmds[2];
	char	**temp[2];

	cmds[0] = NULL;
	temp[1] = get_trimmed(args);
	while (args[++i])
	{
		cmds[1] = ft_lstlast(cmds[0]);
		if (i == 0 || (args[i][0] == '|' && args[i + 1] && args[i + 1][0]))
		{
			i += args[i][0] == '|';
			ft_lstadd_back(&cmds[0], ft_lstnew(int_var()));
			cmds[1] = ft_lstlast(cmds[0]);
		}
		temp[0] = args;
		cmds[1]->content = get_params(cmds[1]->content, temp, &i);
		if (i < 0)
			return (stop_fill(cmds[0], args, temp[1]));
		if (!args[i])
			break ;
	}
	m_free(&temp[1]);
	m_free(&args);
	return (cmds[0]);
}