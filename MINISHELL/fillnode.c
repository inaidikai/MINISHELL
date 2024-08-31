/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillnode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 13:41:43 by inkahar           #+#    #+#             */
/*   Updated: 2024/08/31 15:21:04 by inkahar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

char **dup_node(char **av)
{
    int i = 0;
    char **arr = NULL;
    int n = 0;
    n = m_size(av);
    arr = malloc(sizeof(char **) * n + 1);
    while(av[i])
    {
        arr[i] = ft_strdup(av[i]);
        if(!arr[i])
        {
            return(NULL);
        }
        i++;
    }
    arr[i] = "\0";
    return(arr);
}
static t_str	*get_params(t_str *node, char **a[2], int *i)
{
	if (a[0][*i])
	{
		if (a[0][*i][0] == '>' && a[0][*i + 1] && a[0][*i + 1][0] == '>')
			node = get_outfile2(node, a[1], i);
		else if (a[0][*i][0] == '>')
			node = get_outfile1(node, a[1], i);
		else if (a[0][*i][0] == '<' && a[0][*i + 1] && \
			a[0][*i + 1][0] == '<')
			node = get_infile2(node, a[1], i);
		else if (a[0][*i][0] == '<')
			node = get_infile1(node, a[1], i);
		else if (a[0][*i][0] != '|')
			node->full_cmd = m_exdup(node->full_cmd, a[1][*i]);
		else
		{
			errno(PIPENDERR, NULL, 2);
			*i = -2;
		}
		return (node);
	}
	errno(PIPENDERR, NULL, 2);
	*i = -2;
	return (node);
}

char **gettrimmed(char **av)
{
    char **temp = NULL;
    char *arr;
    int j  =0;
    temp = dup_node(av);
    while(temp[j])
    {
        arr = clean_trim(temp[j], 0 , 0);
        free(temp[j]);
        temp[j] = arr;
    }
    return(temp);
}
static t_list	*stop_fill(t_list *cmds, char **args, char **temp)
{
	ft_lstclear(&cmds, free_content);
	m_free(&temp);
	m_free(&args);
	return (NULL);
}
t_list *fillnode(char **av, int i)
{
    t_list *cmd[2];
    char **temp[2];

    cmd[0] = NULL;
    temp[1] = gettrimmed(av);
   
    while(av[++i])
    {
        cmd[1] = ft_lstlast(cmd[0]);
        if( i == 0|| (av[i][0] == '|' && av[i + 1] && av[i+1][0]))
        {
            i+= av[i][0] == '|';
            ft_lstadd_back(&cmd[0], ft_lstnew(int_var));
            cmd[1] = ft_lstlast(cmd[0]);
        }
        temp[0] = av;
        cmd[1]->content = get_params(cmd[1]->content, temp, &i);
        if (i < 0)
			return (stop_fill(cmd[0], av, temp[1]));
		if (!av[i])
			break ; 
	}
	m_free(&temp[1]);
	m_free(&av);
	return (cmd[0]);
}