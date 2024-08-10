/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrx.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymohamm <aymohamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 16:38:27 by aymohamm          #+#    #+#             */
/*   Updated: 2024/08/10 16:39:53 by aymohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_extend_matrix(char **matrix, char *new_entry)
{
	int		i;
	char	**new_matrix;
	i = 0;
	while (matrix && matrix[i])
		i++;
	new_matrix = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new_matrix)
		return (NULL);
	i = 0;
	while (matrix && matrix[i])
	{
		new_matrix[i] = matrix[i];
		i++;
	}
	new_matrix[i] = new_entry;
	new_matrix[i + 1] = NULL;
	if (matrix)
		free(matrix);
	return (new_matrix);
}
