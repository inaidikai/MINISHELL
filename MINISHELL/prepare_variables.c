/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_variables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymohamm <aymohamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 13:24:20 by aymohamm          #+#    #+#             */
/*   Updated: 2024/08/31 12:31:02 by aymohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_pwd(t_prompt *prompt, char *store)
{
	store = getcwd(NULL, 0);
	prompt->env = mini_setenv("PWD", store, prompt->env, 3);
	free(store);
}

static void	set_shlvl(t_prompt *prompt, char *store)
{
	char	*num;

	store = mini_getenv("SHLVL", prompt->env, 5);
	if (!store || ft_atoi(store) <= 0)
		num = ft_strdup("1");
	else
		num = ft_itoa(ft_atoi(store) + 1);
	free(store);
	prompt->env = mini_setenv("SHLVL", num, prompt->env, 5);
	free(num);
}

static void	set_path(t_prompt *prompt, char *store)
{
	store = mini_getenv("PATH", prompt->env, 4);
	if (!store)
	{
		prompt->env = mini_setenv("PATH", \
		"/usr/local/sbin:/usr/local/bin:/usr/bin:/bin", prompt->env, 4);
	}
	free(store);
}

static void	set_underscore(t_prompt *prompt, char *argv, char *store)
{
	store = mini_getenv("_", prompt->env, 1);
	if (!store)
	{
		prompt->env = mini_setenv("_", argv, prompt->env, 1);
	}
	free(store);
}

t_prompt	prepare_variables(t_prompt prompt, char *store, char **av)
{
	set_pwd(&prompt ,store);
	set_shlvl(&prompt, store);
	set_path(&prompt, store);
	set_underscore(&prompt, av[0], store);
	return (prompt);
}
