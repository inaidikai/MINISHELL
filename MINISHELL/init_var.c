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
void free_content(void *content)
{
    t_str *node;
    node = content;
	m_free(&node->full_cmd);
	free(node->full_path);
	if (node->infile != STDIN_FILENO)
		close(node->infile);
	if (node->outfile != STDOUT_FILENO)
		close(node->outfile);
	free(node);
}
