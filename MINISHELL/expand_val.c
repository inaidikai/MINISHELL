/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_val.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 14:06:42 by aymohamm          #+#    #+#             */
/*   Updated: 2024/08/18 13:47:54 by inkahar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *replace_val(char *str, int i, t_prompt *prompt)
{
    char *pre;
    int pos;
    char *result;
    char *val;

    pos = ft_strchr(&str[i], "|\"\'$?>< ") + (ft_strchr("$?", str[i]) != 0);
    if (pos == -1)
        pos = ft_strlen(&str[i]) - 1;
    pre = ft_substr(str, 0, i - 1);
    val = mini_getenv(&str[i], prompt->env, ft_strchr(&str[i], "\"\'$|>< "));
    if (!val && str[i] == '$')
        val = ft_itoa(prompt->pid);
    else if (!val && str[i] == '?')
        val = ft_itoa(g_sig);

    result = ft_strjoin(pre, val);
    free(pre);
    pre = ft_strjoin(result, &str[i + pos]);
    free(val), free(result), free(str);;
    return pre;
}



char *expand_val(char *str, int i, int fq[2], t_prompt *prompt)
{
    fq[0] = 0;
    fq[1] = 0;
    char *expanded;
    
    while (str && str[++i]) {
        if (str[i] == '\'' && !fq[1]) fq[0] = !fq[0];
        if (str[i] == '\"' && !fq[0]) fq[1] = !fq[1];
        if (!fq[0] && str[i] == '$' && str[i + 1] &&
            ((str[i + 1] == '/' || str[i + 1] == '~' || str[i + 1] == '%' ||
              str[i + 1] == '{' || str[i + 1] == '}' || str[i + 1] == ':' ||
              str[i + 1] == ';' || str[i + 1] == ' ' || str[i + 1] == '\0') &&
              !fq[1]) ||
            ((str[i + 1] == '/' || str[i + 1] == '~' || str[i + 1] == '%' ||
              str[i + 1] == '{' || str[i + 1] == '}' || str[i + 1] == ':' ||
              str[i + 1] == ';' || str[i + 1] == ' ' || str[i + 1] == '\"' ||
              str[i + 1] == '\0') && fq[1])) {
            expanded = replace_val(str, ++i, fq);
            if (expanded)
                return (expand(expanded, -1, fq, prompt));
        }
    }
    return str;
}
