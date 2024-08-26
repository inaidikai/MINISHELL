/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymohamm <aymohamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 07:22:09 by aymohamm          #+#    #+#             */
/*   Updated: 2024/08/26 08:16:05 by aymohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.c"


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

void reset_signals_to_default(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}