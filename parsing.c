/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:00:00 by aymohamm          #+#    #+#             */
/*   Updated: 2024/08/25 16:54:04 by inkahar          ###   ########.fr       */
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
	while(i-- > 0)
		waitpid(-1, &g_sig, 0);
	if(!f_exit && g_sig == 13)
		g_sig = 0;
	if(g_sig > 255)
		g_sig = g_sig / 255;
	if(av && f_exit)
	{
		ft_lstclear(&p->cmds, free_content);
		return(NULL);
	}
	return (p);
}
// if (!p->cmds)
// 		return (p);
// 	i = ft_lstsize(p->cmds);
// 	g_status = builtin(p, p->cmds, &is_exit, 0);
// 	while (i-- > 0)
// 		waitpid(-1, &g_status, 0);
// 	if (!is_exit && g_status == 13)
// 		g_status = 0;
// 	if (g_status > 255)
// 		g_status = g_status / 255;
// 	if (args && is_exit)
// 	{
// 		ft_lstclear(&p->cmds, free_content);
// 		return (NULL);
// 	}
// 	return (p);