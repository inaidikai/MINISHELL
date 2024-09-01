#include "minishell.h"
// typedef struct s_str
// {
// 	char	**full_cmd;
// 	char	*full_path;
// 	int		infile;
// 	int		outfile;
// }	
// void int_var(t_str *var)
// {
//     var->full_cmd = NULL;
//     var->full_path = NULL;
//     var->infile = 0;
//     var->outfile = 0;
t_str *int_var(void)
{
	t_str	*str;
	str = malloc(sizeof(t_str));
	if (!str)
	{
		return NULL;
	}
	str->full_cmd = NULL;
	str->full_path = NULL;
	str->infile = STDIN_FILENO;
	str->outfile = STDOUT_FILENO;
	return (str);
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
