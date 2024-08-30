/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 16:56:31 by aymohamm          #+#    #+#             */
/*   Updated: 2024/08/26 11:27:51 by inkahar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_aatoi(const char *s, long *n)
{
    int sign = 1;

    *n = 0;
    while (ft_isspace(*s))
        s++;
    if (*s == '-')
        sign = -sign;
    if (*s == '-' || *s == '+')
        s++;
    if (!ft_isdigit(*s))
        return -1;
    while (ft_isdigit(*s))
    {
        *n = 10 * *n + (*s - '0');
        s++;
    }
    if (*s && !ft_isspace(*s))
        return -1;
    *n *= sign;
    return 0;
}

int cmd_exit(t_list *cmd, int *f_exit)
{
    t_str *data;
    long val[2];

    data = cmd->content;
    *f_exit = !cmd->next;
    if (*f_exit)
        ft_putstr_fd("exit\n", 2);
    if (!data->full_cmd || !data->full_cmd[1])
        return (0);
    val[1] = ft_aatoi(data->full_cmd[1], &val[0]);
    if (val[1] == -1)
    {
        ft_putstr_fd("minishell: exit: ", 2);
        ft_putstr_fd(data->full_cmd[1], 2);
        ft_putstr_fd(": numeric argument required\n", 2);
        return (255);
    }
    else if (data->full_cmd[2])
    {
        *f_exit = 0;
        ft_putstr_fd("minishell: exit: too many arguments\n", 2);
        return (1);
    }
    val[0] %= 256 + 256 * (val[0] < 0);
    return (val[0]);
}

