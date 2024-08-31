/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:07:17 by inkahar           #+#    #+#             */
/*   Updated: 2024/08/31 14:38:20 by inkahar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*array;

	if (count != 0 && UINT_MAX / count < size)
		return (NULL);
	array = ((void *)malloc(count * size));
	if (array == NULL)
		return (NULL);
	ft_bzero(array, (count * size));
	return (array);
}
