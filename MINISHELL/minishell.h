#ifndef MINISHELL_H
#define MINISHELL_H

# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include "libft/libft.h"
# include <dirent.h>
# include <sys/ioctl.h>

extern int	g_sig;

typedef struct s_prompt
{
    t_list *cmds;
	char	**env;
	pid_t	pid;
}			t_prompt;

typedef struct s_str
{
	char	**full_cmd;
	char	*full_path;
	int		infile;
	int		outfile;
}			t_str;


char	**dup_env(char **envp);
t_prompt	prepare_variables(t_prompt prompt, char **av);
char	*getprompt(void);
char	**mini_setenv(char *var, char *value, char **envp, int n);
char	*mini_getenv(char *var, char **envp, int n);
char	**ft_extend_matrix(char **matrix, char *new_entry);
int	ft_strchr_i(const char *s, int c);
#endif