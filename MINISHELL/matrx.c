/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrx.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 16:38:27 by aymohamm          #+#    #+#             */
/*   Updated: 2024/08/31 22:16:00 by inkahar          ###   ########.fr       */
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

// char **m_exdup(char **in, char *newstr) {
//     char **out;
//     int len;
//     int i;
	
// 	i = -1;
//     if (!newstr) {
//         return in;
//     }
//     len = m_size(in);
//     // len = 2;
//     out = malloc(sizeof(char *) * (2 + 2));
//     if (!out) {
//         return in; // Early return if allocation fails
//     }
//     out[len + 1] = NULL;
//     for (i = 0; i < len; i++) {
//         out[i] = ft_strdup(in[i]);
//         if (!out[i]) {
//             while (--i >= 0) {
//                 free(out[i]);
//             }
//             free(out);
//             return in; // Return original if duplication fails
//         }
//     }
//     out[i] = ft_strdup(newstr);
//     if (!out[i]) {
//         while (--i >= 0) {
//             free(out[i]);
//         }
//         free(out);
//         return in;
//     }
//     m_free(&in); // Frees `in` after successful duplication
//     return out;
// }
char	**m_exdup(char **in, char *newstr)
{
	char	**out;
	int		len;
	int		i;

	i = -1;
	out = NULL;
	if (!newstr)
		return (in);
	len = m_size(in);
	out = malloc(sizeof(char *) * (len + 2));
	out[len + 1] = NULL;
	if (!out)
		return (in);
	while (++i < len)
	{
		out[i] = ft_strdup(in[i]);
		if (!out[i])
		{
			m_free(&in);
			m_free(&out);
		}
	}
	out[i] = ft_strdup(newstr);
	m_free(&in);
	return (out);
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
// void md_free(char **m)
// {
// 	int i;
// 	i = 0;
// 	while(m )
// }

int m_size(char **m) {
    int i = 0;

    // if (m[0] == NULL || m[0][0] == '\0') {
    //     return 0;
    // }
	// if (!m || !m[0]) {
    //     return 0;
    // }
	// printf("here");
	
    while (m && m[i]) {
        i++;
    }
    return i;
}



char	**m_replace(char ***big, char **small, int n)
{
	char	**aux;
	int		i[3];

	i[0] = -1;
	i[1] = -1;
	i[2] = -1;
	if (!big || !*big || n < 0 || n >= m_size(*big))
		return (NULL);
	aux = ft_calloc(m_size(*big) + m_size(small), sizeof(char *));
	while (aux && big[0][++i[0]])
	{
		if (i[0] != n)
			aux[++i[2]] = ft_strdup(big[0][i[0]]);
		else
		{
			while (small && small[++i[1]])
				aux[++i[2]] = ft_strdup(small[i[1]]);
		}
	}
	m_free(big);
	*big = aux;
	return (*big);
}
