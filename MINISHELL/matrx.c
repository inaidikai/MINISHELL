/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrx.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymohamm <aymohamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 16:38:27 by aymohamm          #+#    #+#             */
/*   Updated: 2024/08/26 08:14:23 by aymohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	m_put(char **m, int nl, int fd)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (m && m[i])
	{
		if (nl)
			count += ft_putendl_fd(m[i], fd);
		else
			count += ft_putstr_fd(m[i], fd);
		i++;
	}
	return (count);
}

char	**m_exdup(char **matrix, char *new_entry)
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

void	m_free(char ***m)
{
	int	i;

	i = 0;
	while (m && m[0] && m[0][i])
	{
		free(m[0][i]);
		i++;
	}
	if (m)
	{
		free(m[0]);
		*m = NULL;
	}
}
int m_size(char **m)
{
    int i;

    i = 0;
    while (m && m[i])
        i++;
    return (i);
}


char **m_replace(char ***old, char **new, int oi)
{
    char **result;
    int i[3] = {-1, -1, -1};

    if (!old || !*old || oi < 0 || oi >= m_size(*old))
        return NULL;

    result = ft_calloc(m_size(*old) + m_size(new), sizeof(char *));
    
    while (result && (*old)[++i[0]])
    {
        if (i[0] != oi)
            result[++i[2]] = ft_strdup((*old)[i[0]]);
        else
        {
            while (new && new[++i[1]])
                result[++i[2]] = ft_strdup(new[i[1]]);
        }
    }
	m_free(old);
    *old = result;
    return *old;
}
