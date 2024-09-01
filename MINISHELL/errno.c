#include "minishell.h"
void *errno(errorcode OPCODE, char *s, int flag)
{
	flag = g_sig;
	(void)*s; 
	(void)flag; 

	if(OPCODE == UNCLOSEDPARA)
		printf("%s", "sister/brother u put unclosed params\n");
	else if(OPCODE == NOTDIR)
		printf("%s", "no directory");
	else if(OPCODE == NPERM)
		printf("%s", "no PERMISSION");
	else if(OPCODE == PIPENDERR)
		printf("%s", "no directory");
	else if (OPCODE == NO_CMD)
		printf("%s", "minishell: command not found: \n");
	else if (OPCODE == CHECK_DIR)
		printf("%s", "minishell: Is a directory: ");
	else if (OPCODE == ERR_PIPE)
		printf( "%s", "minishell: error creating pipe\n");
	else if (OPCODE == ERR_FORK)
		printf("%s", "minishell: fork failed\n");
	else if (OPCODE == ERR_DUP)
		printf("%s", "minishell: dup2 failed\n");
	else if (OPCODE == NOFILE_DIR)
		printf("%s", "minishell: SEROFR");
	return (NULL);
}   