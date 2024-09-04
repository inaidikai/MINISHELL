/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:11:37 by inkahar           #+#    #+#             */
/*   Updated: 2024/09/04 20:12:07 by inkahar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_str	*int_var(void)
{
	t_str	*str;

	str = malloc(sizeof(t_str));
	if (!str)
	{
		return (NULL);
	}
	str->full_cmd = NULL;
	str->full_path = NULL;
	str->infile = STDIN_FILENO;
	str->outfile = STDOUT_FILENO;
	return (str);
}

void	free_content(void *content)
{
	t_str	*node;

	node = content;
	m_free(&node->full_cmd);
	free(node->full_path);
	if (node->infile != STDIN_FILENO)
		close(node->infile);
	if (node->outfile != STDOUT_FILENO)
		close(node->outfile);
	free(node);
}
