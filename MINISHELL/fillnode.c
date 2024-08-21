#include "minishell.h"
int dup_node(char **av)
{
    int i = 0;
    char **arr = NULL;
    int n = m_size(av);
    arr = malloc(sizeof(char **)*n+1);
    while(av[i])
    {
        arr[i] = ft_strdup(av[i]);
       if(!arr[i])
        {
            return(NULL);
        }
        i++;
    }
    arr[i] = '/0';
    return(arr);
}

int gettrimmed(char **av)
{
    char **temp = NULL;
    char *arr;
    temp = dup_node(av);
    while(temp[i])
    {
        arr = ft
    }
}

int fillnode(char **av, int i)
{
    t_list *cmd[2];
    char **temp[2];

    cmd[0] = NULL;
    temp[1] = gettrimmed(av);
}