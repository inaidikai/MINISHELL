/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 12:30:38 by aymohamm          #+#    #+#             */
/*   Updated: 2024/09/03 15:29:49 by inkahar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	**m_env(char **m)
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


char **mini_setenv(char *var, char *value, char **envp, int n) {
    int i[2];
    char *aux[2];

    if (n < 0)
        n = ft_strlen(var);
    i[0] = -1;
    aux[0] = ft_strjoin(var, "=");
    aux[1] = ft_strjoin(aux[0], value);
    free(aux[0]); // Freeing aux[0] as it's no longer needed

    while (!ft_strchr(var, '=') && envp && envp[++i[0]]) {
        i[1] = n;
        if (i[1] < ft_strchr_i(envp[i[0]], '='))
            i[1] = ft_strchr_i(envp[i[0]], '=');
        if (!ft_strncmp(envp[i[0]], var, i[1])) {
            // Replace the old environment variable with the new one
            free(envp[i[0]]); // Free the old value
            envp[i[0]] = aux[1]; // Assign new value
            return envp;
        }
    }

    // If no matching variable was found, add the new variable
    envp = m_exdup(envp, aux[1]);
    free(aux[1]); // Free aux[1] as it's no longer needed

    return envp;
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
