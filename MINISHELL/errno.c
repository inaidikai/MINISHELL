#include "minishell.h"
void errno(errorcode OPCODE, char *s, int flag)
{
	flag = g_sig;

	if(OPCODE == UNCLOSEDPARA)
		printf("%s", "sister u put unclosed params\n");
	if(OPCODE == NDIR)
		printf("%s", "no directory");
	if(OPCODE == NPERM)
		printf("%s", "no PERMISSION");
	if(OPCODE == PIPENDERR)
		printf("%s", "no directory");
}