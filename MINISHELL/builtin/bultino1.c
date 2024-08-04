#include "minishell.h"
int echo(char *s)
{
	int i  =0;
	int flag  = 0;
	while(s[i] && ft_strncmp(s[i], '-n'))
	{
		i++;
		flag = 1;
	}
	while(s[i])
	{
		printf("%s", s[i]);
		i++;
	}
	if(flag == 0)
	{
		printf("/n");
	}
	return 0;
}
int cd(char *path)
{
	char *home = getenv("HOME");
	if(!path)
		chdir(home);
	if (!chdir(path))
	{
		perror(0);
		return -1;
	}
	return 0;
}
int pwd(char *str)
{
	char buf[1024];
	if(ft_strncmp(*str, "pwd"))
	{
		if(getcwd(buf, sizeof(buf)) == NULL)
		{
			perror(0);
		}
		printf("%s", buf);
	}
}