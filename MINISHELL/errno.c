#include "minishell.h"
void chk(errorcode OPCODE)
{
	if(OPCODE == UNCLOSEDPARA)
		printf("%s", "sister u put unclosed params\n");
}