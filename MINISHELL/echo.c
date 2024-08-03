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
int cd()
{
	chdir
}