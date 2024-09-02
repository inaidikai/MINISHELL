/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:52:43 by inkahar           #+#    #+#             */
/*   Updated: 2024/09/02 23:19:33 by inkahar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char *ft_strdup(const char *s1)
{
    char *d;
    size_t size;

    if (!s1)
        return NULL;
    size = ft_strlen(s1);
    d = (char *)malloc(size + 1);
    if (!d)
        return NULL;
    ft_strlcpy(d, s1, size + 1);
    return d;
}
