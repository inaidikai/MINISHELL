/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymohamm <aymohamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 10:22:27 by aymohamm          #+#    #+#             */
/*   Updated: 2024/08/10 18:10:25 by aymohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_sig;


void handle_int(int signum)
{
    if(signum == SIGINT)
    {
        g_sig =  1;
        write(1, "\n", 1);
        rl_on_new_line();
        rl_redisplay();
    }
}

static int start_prompt(void)
{
	char	*store;
    char    *read;
    signal(SIGINT, handle_int);
    signal(SIGQUIT, handle_int);
	while (1)
	{
        
        store = getprompt();
        read = readline(store);
        // free(store);
        if (!read)              
            break;
        // if (!parsing(read, prompt))
        // {
        //     free(read);
        //     break;
        // }
        // free(read);
	}
	return (g_sig);
}



static t_prompt	init_env(char **av, char **env)
{
    t_prompt pre_shell;
    char *store;

    store = NULL;
    pre_shell.cmds = NULL;
    pre_shell.env = dup_env(env);
    g_sig = 0;
    //process pid
    pre_shell = prepare_variables(pre_shell, av);
    return (pre_shell);
    
}


int main(int ac, char **av, char **env)
{
    t_prompt pre_shell;
    (void)ac;
    
    pre_shell = init_env(av, env);
    g_sig = start_prompt();
    return (g_sig);
}



