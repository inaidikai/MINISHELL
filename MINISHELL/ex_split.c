/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 21:40:46 by aymohamm          #+#    #+#             */
/*   Updated: 2024/08/31 15:21:48 by inkahar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *expand(char *str, t_prompt *prompt)
{
    char *ex_val;
    char *ex_pa;
    int fq[2] = {0, 0};

    ex_val = expand_val(str, -1, fq, prompt);
    if (!ex_val)
        return NULL;

    ex_pa = expand_tilde(ex_val, -1, fq, mini_getenv("HOME", prompt->env, 4));
    // free(ex_val);

    return ex_pa;
}

static void handle_split(char **av, t_prompt *prompt, int i)
{
    char **splitted;
	(void)prompt;

    splitted = cmdsubsplit(av[i], "<|>");
    if (!splitted)
        return;

    m_replace(&av, splitted, i);
    i += m_size(splitted) - 1;
    // m_free(&splitted);
}

char **ex_split(char **av, t_prompt *prompt)
{
    int i;
    i = -1;

    while (av && av[++i])
    {
        av[i] = expand(av[i], prompt);
        if (!av[i])
            return NULL;

        handle_split(av, prompt, i);
    }
    return av;
}
