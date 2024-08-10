#include "minishell.h"

int g_sig;
// int ft_cmtrim(char *read)
// {
    
// }
static char *readu(void)
{
    return(strdup("minishell"));
}
int	main(int ac, char **av, char **ev)
{    if(ac == 1 || av[1][0]==  1 || !ev)
        return 0;

char *red ;
char *store ;

    while(1)
    { 
        signal(SIGINT, handle_int);
        signal(SIGQUIT, handle_int);
        g_sig = 0;
        store = readu();
        red = readline(store);
        free(store);
    }
    free(red);
   return(g_sig);
}
