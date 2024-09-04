/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:08:39 by inkahar           #+#    #+#             */
/*   Updated: 2024/09/04 20:10:07 by inkahar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_here_str(char *str[2], size_t len, char *limit, char *caution)
{
	char	*temp;

	while (g_sig != 130 && (!str[0] || ft_strncmp(str[0], limit, len)
			|| ft_strlen(limit) != len))
	{
		temp = str[1];
		str[1] = ft_strjoin(str[1], str[0]);
		free(temp);
		free(str[0]);
		str[0] = readline("> ");
		if (!str[0])
		{
			printf("%s(wanted '%s\')\n", caution, limit);
			break ;
		}
		temp = str[0];
		str[0] = ft_strjoin(str[0], "\n");
		free(temp);
		len = ft_strlen(str[0]) - 1;
	}
	free(str[0]);
	return (str[1]);
}

int	get_here_doc(char *str[2], char *aux[2])
{
	int	fd[2];

	g_sig = 0;
	if (pipe(fd) == -1)
	{
		errno(PERR, NULL, 1);
		return (-1);
	}
	str[1] = get_here_str(str, 0, aux[0], aux[1]);
	write(fd[1], str[1], ft_strlen(str[1]));
	free(str[1]);
	close(fd[1]);
	if (g_sig == 130)
	{
		close(fd[0]);
		return (-1);
	}
	return (fd[0]);
}
