/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:14:25 by inkahar           #+#    #+#             */
/*   Updated: 2024/09/05 13:57:41 by inkahar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
	{
		return 0;
	}
	while (s[i] != '\0')
	{
		write(fd, &s[i] , 1);
		i++;
	}
	 write(fd, " : ", 4);
	return 0;
}
