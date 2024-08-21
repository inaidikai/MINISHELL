/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillnodeutils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:21:17 by inkahar           #+#    #+#             */
/*   Updated: 2024/08/21 14:46:05 by inkahar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int count_imposters(char *s)
{
    int count = 0;
    int singleq = 0;
    int doubleq = 0;
    int i = 0;
    
    while(s[i])
    {
        singleq = (singleq + (!doubleq && s[i]== '\'')) % 2;
        doubleq = (doubleq + (!singleq && s[i]== '\"')) % 2;
        if((s[i] == '\'' && !doubleq)|| (s[i] == '\"' && !singleq));
            count++;
        i++;
    }
    if(singleq || doubleq)
         return -1;
    return(count);
}

char *clean_trim(char *s)