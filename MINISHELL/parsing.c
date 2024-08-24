/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymohamm <aymohamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:00:00 by aymohamm          #+#    #+#             */
/*   Updated: 2024/08/24 22:26:09 by aymohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*parsing(char **av, t_prompt *p)
{
    int	f_exit;
	int	i;

	f_exit = 0;
	p->cmds = fillnode(ex_split(av, p), -1);
	if (!p->cmds)
		return (p);
	i = ft_lstsize(p->cmds);
	g_sig = builtin(p, p->cmds, &f_exit, 0);
	//signals
	// return (p);
}