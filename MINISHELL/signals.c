/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 07:22:09 by aymohamm          #+#    #+#             */
/*   Updated: 2024/08/31 17:06:34 by inkahar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void handle_int(int signum)
{
    if(signum == SIGINT)
    {
        g_sig =  130;
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
