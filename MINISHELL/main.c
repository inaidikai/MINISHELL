/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 10:22:27 by aymohamm          #+#    #+#             */
/*   Updated: 2024/09/03 17:34:56 by inkahar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_sig;

static void free_env(t_prompt *p) {
    int i = 0;
    while (p->env[i]) {
        free(p->env[i]);
        i++;
    }
    free(p->env);
}


// static int start_prompt(t_prompt *p)
// {
// 	char	*store;
//     char    *read;
//     char **input;
    
//     signal(SIGINT, handle_int);
//     signal(SIGQUIT, SIG_IGN);
//     // store = "";
// 	while (1)
// 	{
//         store = getprompt();
//         read = readline(store);
//         free(store);
//         if (!read)              
//             break;
//        input = lexer(read, p);
//         free(read);
//         if (!input) 
//            break;
//         // free(input);
// 	}
//     free_env(p->env);
// 	return (g_sig);
// }
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
    t_prompt pre_shell;
    char *store;

    store = NULL;
    pre_shell.cmds = NULL;
    pre_shell.env = m_dup(env);
    // free(env);
    g_sig = 0;
    start_process(&pre_shell);
    pre_shell = prepare_variables(pre_shell, store, av);
    return (pre_shell);
    
}


// int main(int ac, char **av, char **env)
// {
//     t_prompt pre_shell;

//     (void)ac;
    
//     pre_shell = init_env(av, env);
//     g_sig = start_prompt(&pre_shell);
//     return (g_sig);
// }



int main(int ac, char **argv, char **envp)
{
    char *str;
    char *out;
    (void)ac;
    t_prompt prompt;

    prompt = init_env(argv, envp);
    while (1)
    {
        signal(SIGINT, handle_int);
        signal(SIGQUIT, SIG_IGN);
        str = mini_getprompt(prompt);
        if (str)
			out = readline(str);
        else
            out = readline("guest@minishell $ ");
		free(str);
		if(!lexer(out, &prompt))
            break;
    }
    free_env(&prompt);
    exit(g_sig);
}






