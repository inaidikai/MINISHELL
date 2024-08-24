#ifndef MINISHELL_H
#define MINISHELL_H

# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/wait.h>
# include "libft/libft.h"
# include <dirent.h>
# include <sys/ioctl.h>

extern int g_sig;

typedef enum e_rrorcode
{
    UNCLOSEDPARA,
} errorcode;


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
char *expand_val(char *str, int i, int fq[2], t_prompt *prompt);
char *expand_tilde(char *str, int i, int fq[2], char *home_dir);
void chk(errorcode OPCODE);
void *lexer(char *store);
char	**cmdsubsplit(char const *s, char *set);
char **m_replace(char ***old, char **new, int oi);
int m_size(char **m);
void	m_free(char ***m);
char **ex_split(char **av, t_prompt *prompt);
void int_var(t_str *var);
void handle_int(int signum);
 
#endif