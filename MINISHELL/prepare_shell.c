/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymohamm <aymohamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 12:30:38 by aymohamm          #+#    #+#             */
/*   Updated: 2024/08/31 12:21:53 by aymohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	**dup_env(char **enpv)
{
	char	**out;
	int		n_rows;
	int		i;

	i = 0;
	n_rows = m_size(enpv);
	out = malloc(sizeof(char *) * (n_rows + 1));
	if (!out)
		return (NULL);
	while (enpv[i])
	{
		out[i] = ft_strdup(enpv[i]);
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
int	ft_strchr_i(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	if (s[i] == (char)c)
		return (i);
	return (-1);
}


char	**mini_setenv(char *var, char *value, char **envp, int n)
{
	int		i;
	char	*new_var;
	char	*new_entry;
	if (n < 0)
		n = ft_strlen(var);
	new_var = ft_strjoin(var, "=");
	new_entry = ft_strjoin(new_var, value);
	free(new_var);
	i = 0;
	while (envp && envp[i])
	{
		int compare_length = n;
		int equal_pos = ft_strchr_i(envp[i], '=');
		if (compare_length < equal_pos)
			compare_length = equal_pos;
		if (!ft_strncmp(envp[i], var, compare_length))
		{
			char *old_entry = envp[i];
			envp[i] = new_entry;
			free(old_entry);
			return (envp);
		}
		i++;
	}
	envp = m_exdup(envp, new_entry);
	free(new_entry);
	return (envp);
}



char	*mini_getenv(char *var, char **envp, int n)
{
	int	i;
	int	n2;

	i = 0;
	if (n < 0)
		n = ft_strlen(var);
	while (!ft_strchr(var, '=') && envp && envp[i])
	{
		n2 = n;
		if (n2 < ft_strchr_i(envp[i], '='))
			n2 = ft_strchr_i(envp[i], '=');
		if (!ft_strncmp(envp[i], var, n2))
			return (ft_substr(envp[i], n2 + 1, ft_strlen(envp[i])));
		i++;
	}
	return (NULL);
}
