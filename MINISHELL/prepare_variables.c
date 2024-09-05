/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_variables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 13:24:20 by aymohamm          #+#    #+#             */
/*   Updated: 2024/09/05 15:22:09 by inkahar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	m_free(char ***m)
{
	int	i;

	i = 0;
	while (m && m[0] && m[0][i])
	{
		free(m[0][i]);
		i++;
	}
	if (m)
	{
		free(m[0]);
		*m = NULL;
	}
}

void	mo_free(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			free(arr[i]);
			i++;
		}
		free(arr);
	}
}

t_prompt	prepare_variables(t_prompt prompt, char *str, char **argv)
{
	char	*num;

	str = getcwd(NULL, 0);
	prompt.env = mini_setenv("PWD", str, prompt.env, 3);
	free(str);
	str = mini_getenv("SHLVL", prompt.env, 5);
	if (!str || ft_atoi(str) <= 0)
		num = ft_strdup("1");
	else
		num = ft_itoa(ft_atoi(str) + 1);
	free(str);
	prompt.env = mini_setenv("SHLVL", num, prompt.env, 5);
	free(num);
	str = mini_getenv("PATH", prompt.env, 4);
	if (!str)
		prompt.env = mini_setenv("PATH", \
		"/usr/local/sbin:/usr/local/bin:/usr/bin:/bin", \
		prompt.env, 4);
	free(str);
	str = mini_getenv("_", prompt.env, 1);
	if (!str)
		prompt.env = mini_setenv("_", argv[0], prompt.env, 1);
	free(str);
	return (prompt);
}
