/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymohamm <aymohamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 21:40:46 by aymohamm          #+#    #+#             */
/*   Updated: 2024/08/18 14:04:35 by aymohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	**ex_split(char **av, t_prompt *prompt)
// {
// 	char	**splitted;
// 	int		i;
// 	int		fq[2];

// 	i = -1;
// 	while (av && av[++i])
// 	{
// 		av[i] = expand_val(av[i], -1, fq, prompt);
// 		av[i] = expand_tilde(av[i], -1, fq, \
// 			mini_getenv("HOME", prompt->env, 4));
// 		splitted = ft_excmd(av[i], "<|>");
//         //matrix
// 	}
// 	return (av);
// }
0