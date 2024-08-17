/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymohamm <aymohamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 17:59:00 by aymohamm          #+#    #+#             */
/*   Updated: 2024/08/17 18:42:33 by aymohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *expand_tilde(char *str, int i, int fq[2], char *home_dir)
{
    char *before;
    char *after;
    char *expanded;

    fq[0] = 0;
    fq[1] = 0;
    while (str && str[++i])
    {
        if (str[i] == '\'' && !fq[1]) fq[0] = !fq[0];
        if (str[i] == '\"' && !fq[0]) fq[1] = !fq[1];
        if (!fq[0] && !fq[1] && str[i] == '~' && (i == 0 || str[i - 1] != '$'))
        {
            before = ft_substr(str, 0, i);
            expanded = ft_strjoin(before, home_dir);
            free(before);
            after = ft_substr(str, i + 1, ft_strlen(str) - i - 1);
            free(str);
            str = ft_strjoin(expanded, after);
            free(after);
            free(expanded);
            return expand_tilde(str, i + ft_strlen(home_dir) - 1, fq, home_dir);
        }
    }
    free(home_dir);
    return str;
}

