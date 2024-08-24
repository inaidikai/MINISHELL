/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymohamm <aymohamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:31:25 by aymohamm          #+#    #+#             */
/*   Updated: 2024/08/04 14:38:21 by aymohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
int	main(int ac, char **av, char **ev)
{
	int	i;

	(void)ac;
	(void)av;
	i = -1;
	if (!ev)
		printf("\n");
	while (ev[++i])
		printf("%s\n", ev[i]);
	return (0);
}