/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymohamm <aymohamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 19:47:12 by aymohamm          #+#    #+#             */
/*   Updated: 2024/08/30 20:18:09 by aymohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int len_count(char *s, char c)
{
 int count;

    if (!s)
        return (0);
    count = 0;
    while (*s)
    {
        if (*s == c)
            count++;
        s++;
    }
    return (count);
}
int	handle_builtin(t_prompt *prompt, t_list *cmd, int *is_exit, int n)
{
	char	**a;

	while (cmd)
	{
		a = ((t_str *)cmd->content)->full_cmd;
		n = 0;
		if (a)
			n = ft_strlen(*a);
		if (a && !ft_strncmp(*a, "exit", n) && n == 4)
			g_sig = cmd_exit(cmd, is_exit);
		else if (!cmd->next && a && !ft_strncmp(*a, "cd", n) && n == 2)
			g_sig = cmd_cd(prompt);
		else if (!cmd->next && a && !ft_strncmp(*a, "export", n) && n == 6)
			g_sig = cmd_export(prompt);
		else if (!cmd->next && a && !ft_strncmp(*a, "unset", n) && n == 5)
			g_sig = cmd_unset(prompt);
		else
		{
			signal(SIGINT, handle_int);
            signal(SIGQUIT, handle_int);
			exec_cmd(prompt, cmd);
		}
		cmd = cmd->next;
	}
	return (g_sig);
}

int	check_builtins(t_str *s)
{
	int		len;

	if (!s->full_cmd)
		return (0);
	if ((s->full_cmd && ft_strchr(*s->full_cmd, '/')) || (s->full_path && \
		ft_strchr(s->full_path, '/')))
		return (0);
	len = ft_strlen(*s->full_cmd);

	if (!ft_strncmp(*s->full_cmd, "echo", len) && len == 4)
		return (1);
	if (!ft_strncmp(*s->full_cmd, "exit", len) && len == 4)
		return (1);
	if (!ft_strncmp(*s->full_cmd, "env", len) && len == 3)
		return (1);
	if (!ft_strncmp(*s->full_cmd, "cd", len) && len == 2)
		return (1);
	if (!ft_strncmp(*s->full_cmd, "unset", len) && len == 5)
		return (1);
	if (!ft_strncmp(*s->full_cmd, "export", len) && len == 6)
		return (1);
	if (!ft_strncmp(*s->full_cmd, "pwd", len) && len == 3)
		return (1);
	return (0);
}

int	cmd_pwd(void)
{
	char	*store;

	store = getcwd(NULL, 0);
	ft_putendl_fd(store, 1);
	free(store);
	return (0);
}

int cmd_echo(t_list *cmd)
{
 int     newline;
    int     i[2];
    char    **argv;
    t_str  *node;

    i[0] = 0;
    i[1] = 0;
    newline = 1;
    node = cmd->content;
    argv = node->full_cmd;
    while (argv && argv[++i[0]])
    {
        if (!i[1] && !ft_strncmp(argv[i[0]], "-n", 2) && \
            (len_count(argv[i[0]], 'n') == \
            (int)(ft_strlen(argv[i[0]]) - 1)))
            newline = 0;
        else
        {
            i[1] = 1;
            ft_putstr_fd(argv[i[0]], 1);
            if (argv[i[0] + 1])
                ft_putchar_fd(' ', 1);
        }
    }
    return (write(1, "\n", newline) == 2);
}