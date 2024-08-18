#include "minishell.h"
// typedef struct s_str
// {
// 	char	**full_cmd;
// 	char	*full_path;
// 	int		infile;
// 	int		outfile;
// }	
void int_var(t_str *var)
{
    var->full_cmd = NULL;
    var->full_path = NULL;
    var->infile = 0;
    var->outfile = 0;
}