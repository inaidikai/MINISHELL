#include "minishell.h"

extern int	g_status;
static void	update_output(char ***matrix, int fd)
{
	char	**aux;
	char	*temp;
	char	*line;

	aux = NULL;
	line = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		temp = ft_strtrim(line, "\n");
		free(line);
		aux = m_exdup(aux, temp);
		free(temp);
	}
	m_free(matrix);
	*matrix = aux;
}

void	exec_custom(char ***out, char *full, char *args, char **envp)
{
	pid_t	pid;
	int		fd[2];
	char	**matrix;

	pipe(fd);
	pid = fork();
	if (!pid)
	{
		close(fd[READ_END]);
		matrix = ft_split(args, ' ');
		dup2(fd[WRITE_END], STDOUT_FILENO);
		close(fd[WRITE_END]);
		if (!access(full, F_OK))
			execve(full, matrix, envp);
		exit (1);
	}
	close(fd[WRITE_END]);
	waitpid(pid, NULL, 0);
	update_output(out, fd[READ_END]);
	close(fd[READ_END]);
}
static char	*get_home(t_prompt prompt)
{
	char	*temp;
	char	*pwd;
	char	*home;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = ft_strdup("∅ ");
	home = mini_getenv("HOME", prompt.env, 4);
	if (home && home[0] && ft_strnstr(pwd, home, ft_strlen(pwd)))
	{
		temp = pwd;
		pwd = ft_strjoin("~", &pwd[ft_strlen(home)]);
		free(temp);
	}
	free(home);
	home = ft_strjoin(BLUE, pwd);
	free(pwd);
	pwd = ft_strjoin(home, " ");
	free(home);
	home = ft_strjoin(" ", pwd);
	free(pwd);
	pwd = ft_strjoin(home, DEFAULT);
	free(home);
	return (pwd);
}

static char	*get_user(t_prompt prompt)
{
	char	**user;
	char	*temp;
	char	*temp2;

	user = NULL;
	temp2 = NULL;
	exec_custom(&user, "/usr/bin/whoami", "whoami", prompt.env);
	if (!user)
		user = m_exdup(user, "guest");
	if (!ft_strncmp(user[0], "root", 4))
		temp2 = ft_strjoin(NULL, RED);
	else if ((int)(user[0][0]) % 5 == 0)
		temp2 = ft_strjoin(NULL, CYAN);
	else if ((int)(user[0][0]) % 5 == 1)
		temp2 = ft_strjoin(NULL, GRAY);
	else if ((int)(user[0][0]) % 5 == 2)
		temp2 = ft_strjoin(NULL, GREEN);
	else if ((int)(user[0][0]) % 5 == 3)
		temp2 = ft_strjoin(NULL, MAGENTA);
	else
		temp2 = ft_strjoin(NULL, YELLOW);
	temp = ft_strjoin(temp2, *user);
	free(temp2);
	m_free(&user);
	return (temp);
}
// char *mini_getprompt(void)
// {
//     return strdup("$minishell ");
// }

char	*mini_getprompt(t_prompt prompt)
{
	char	*temp;
	char	*temp2;
	char	*aux;

	temp = get_user(prompt);
	temp2 = ft_strjoin(temp, "@minishell");
	free(temp);
	aux = get_home(prompt);
	temp = ft_strjoin(temp2, aux);
	free(aux);
	free(temp2);
	if (!g_sig || g_sig == -1)
		temp2 = ft_strjoin(temp, BLUE);
	else
		temp2 = ft_strjoin(temp, RED);
	free(temp);
	temp = ft_strjoin(temp2, "$ ");
	free(temp2);
	temp2 = ft_strjoin(temp, DEFAULT);
	free(temp);
	return (temp2);
}