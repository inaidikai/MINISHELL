/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymohamm <aymohamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 10:22:27 by aymohamm          #+#    #+#             */
/*   Updated: 2024/08/31 12:50:51 by aymohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_sig;

static int start_prompt(t_prompt *p)
{
	char	*store;
    char    *read;
    char **input;
    
    signal(SIGINT, handle_int);
    signal(SIGQUIT, SIG_IGN);
	while (1)
	{
        store = getprompt();
        read = readline(store);
        free(store);
        if (!read)              
            break;
        input = lexer(read, p);
        free(read);
        if (!input) 
            break;
        free(input);
	}
	return (g_sig);
}
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

static t_prompt	init_env(char **av, char **env, t_str *var)
{
    t_prompt pre_shell;
    char *store;

    store = NULL;
    pre_shell.cmds = NULL;
    pre_shell.env = dup_env(env);
    g_sig = 0;
    int_var(var);
    start_process(&pre_shell);
    pre_shell = prepare_variables(pre_shell, store, av);
    return (pre_shell);
    
}


int main(int ac, char **av, char **env)
{
    t_prompt pre_shell;
    t_str var;

    (void)ac;
    
    pre_shell = init_env(av, env, &var);
    g_sig = start_prompt(&pre_shell);
    return (g_sig);
}




