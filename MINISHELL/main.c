/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 10:22:27 by aymohamm          #+#    #+#             */
/*   Updated: 2024/09/05 18:46:23 by inkahar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig = 0;

static void	start_process(t_prompt *p)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		errno(ERR_FORK, NULL, 1);
		m_free(&p->env);
		exit(1);
	}
	if (!pid)
	{
		m_free(&p->env);
		exit(1);
	}
	waitpid(pid, NULL, 0);
	p->pid = pid - 1;
}

static t_prompt	init_env(char **av, char **env)
{
	t_prompt	pre_shell;
	char		*store;

	store = NULL;
	pre_shell.cmds = NULL;
	pre_shell.env = m_dup(env);
	g_sig = 0;
	start_process(&pre_shell);
	pre_shell = prepare_variables(pre_shell, store, av);
	return (pre_shell);
}

int	main(int ac, char **av, char **envp)
{
	char		*str;
	char		*store;
	t_prompt	prompt;

	(void)ac;
	prompt = init_env(av, envp);
	while (1)
	{
		signal(SIGINT, handle_int);
		signal(SIGQUIT, SIG_IGN);
		str = mini_getprompt();
		if (str)
			store = readline(str);
		free(str);
		if (!lexer(store, &prompt))
			break ;
	}
	free_env(&prompt);
	exit(g_sig);
}
