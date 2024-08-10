#include "minishell.h"
void handle_int(int signum)
{
    if(signum == SIGINT)
    {
        g_sig =  1;
        write(1, "\n", 1);
        rl_on_new_line();
        rl_redisplay();
        printf("%s", "minishell");
    }
} 