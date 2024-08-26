/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymohamm <aymohamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 12:30:38 by aymohamm          #+#    #+#             */
/*   Updated: 2024/08/26 08:05:01 by aymohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static int	ft_size(char **store)
{
	int	size;

	size = 0;
	while (store[size])
		size++;
	return (size);
}

char	**dup_env(char **envp)
{
	char	**dup;
	int		i;
	int		size;

	size = ft_size(envp);
	dup = (char **)malloc(sizeof(char *) * (size + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < size)
	{
		dup[i] = ft_strdup(envp[i]);
		if (!dup[i])
		{
			while (--i >= 0)
				free(dup[i]);
			free(dup);
			return (NULL);
		}
		i++;
	}
	dup[i] = NULL;
	return (dup);
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
