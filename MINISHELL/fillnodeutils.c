/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillnodeutils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:21:17 by inkahar           #+#    #+#             */
/*   Updated: 2024/09/04 20:03:43 by inkahar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_imposters(char *s)
{
	int	count;
	int	singleq;
	int	doubleq;
	int	i;

	count = 0;
	singleq = 0;
	doubleq = 0;
	i = 0;
	while (s[i])
	{
		singleq = (singleq + (!doubleq && s[i] == '\'')) % 2;
		doubleq = (doubleq + (!singleq && s[i] == '\"')) % 2;
		if ((s[i] == '\'' && !doubleq) || (s[i] == '\"' && !singleq))
			count++;
		i++;
	}
	if (singleq || doubleq)
		return (-1);
	return (count);
}

char	*clean_trim(char *s, int singleq, int doubleq)
{
	char	*trim;
	int		i[2];
	int		count;

	i[1] = -1;
	i[0] = 0;
	count = 0;
	count = count_imposters(s);
	if (!s && count == -1)
		return (NULL);
	trim = malloc(sizeof(char *) * ft_strlen(s) + count + 1);
	if (!trim)
		return (NULL);
	while (s[i[0]])
	{
		singleq = (singleq + (!doubleq && s[i[0]] == '\'')) % 2;
		doubleq = (doubleq + (!singleq && s[i[0]] == '\"')) % 2;
		if ((s[i[0]] != '\'' || doubleq) && (s[i[0]] != '\"' || singleq)
			&& (++i[1] >= 0))
			trim[i[1]] = s[i[0]];
		i[0]++;
	}
	trim[++i[1]] = '\0';
	return (trim);
}
