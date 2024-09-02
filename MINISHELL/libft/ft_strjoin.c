/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:24:52 by inkahar           #+#    #+#             */
/*   Updated: 2024/09/02 23:31:43 by inkahar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len_s1;
	int		len_s2;
	char	*s3;
	int		i;
	int		j;

	// If both strings are NULL, return NULL
	if (s1 == NULL && s2 == NULL)
		return (NULL);

	// Calculate the length of s1 and s2
	if (s1 != NULL)
		len_s1 = ft_strlen(s1);
	else
		len_s1 = 0;

	if (s2 != NULL)
		len_s2 = ft_strlen(s2);
	else
		len_s2 = 0;

	// Allocate memory for the new string
	s3 = (char *)malloc(len_s1 + len_s2 + 1);
	if (s3 == NULL)
		return (NULL);

	// Copy s1 into s3
	i = 0;
	while (i < len_s1)
	{
		s3[i] = s1[i];
		i++;
	}

	// Copy s2 into s3, right after s1
	j = 0;
	while (j < len_s2)
	{
		s3[i + j] = s2[j];
		j++;
	}

	// Null-terminate the new string
	s3[i + j] = '\0';

	return (s3);
}
