/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errno.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 19:53:20 by inkahar           #+#    #+#             */
/*   Updated: 2024/09/05 15:28:32 by inkahar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*errno(t_errorcode OPCODE, char *s, int flag)
{
	g_sig = flag;
	ft_putendl_fd(s, 2);
	if (OPCODE == UNCLOSEDPARA)
		ft_putstr_fd("sister/brother u put unclosed params\n", 2);
	else if (OPCODE == NOTDIR)
		ft_putstr_fd("no directory", 2);
	else if (OPCODE == NPERM)
		ft_putstr_fd("no PERMISSION", 2);
	else if (OPCODE == PIPENDERR)
		ft_putstr_fd("no directory", 2);
	else if (OPCODE == NO_CMD)
		ft_putstr_fd("minishell: command not found: \n", 2);
	else if (OPCODE == CHECK_DIR)
		ft_putstr_fd("minishell: Is a directory: ", 2);
	else if (OPCODE == ERR_PIPE)
		ft_putstr_fd("minishell: error creating pipe\n", 2);
	else if (OPCODE == ERR_FORK)
		ft_putstr_fd("minishell: fork failed\n", 2);
	else if (OPCODE == ERR_DUP)
		ft_putstr_fd("minishell: dup2 failed\n", 2);
	else if (OPCODE == NOFILE_DIR)
		ft_putstr_fd("minishell: SEROFR", 2);
	return (NULL);
}
