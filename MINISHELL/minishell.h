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
	NOTDIR,
	NOFILE_DIR,
	NPERM,
	NDIR,                                                                                                                                     
	PIPENDERR,
	PERR,
	NO_CMD,
	CHECK_DIR,
	ERR_PIPE,
	ERR_FORK,
	ERR_DUP,

} errorcode;

# define READ_END 0
# define WRITE_END 1


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


char		**dup_env(char **envp);
t_prompt	prepare_variables(t_prompt prompt,char *store, char **av);
char		*getprompt(void);
char		**mini_setenv(char *var, char *value, char **envp, int n);
char		*mini_getenv(char *var, char **envp, int n);
char		**m_exdup(char **matrix, char *new_entry);
int			ft_strchr_i(const char *s, int c);
char 		*expand_val(char *str, int i, int fq[2], t_prompt *prompt);
char 		*expand_tilde(char *str, int i, int fq[2], char *home_dir);
void		*errno(errorcode OPCODE, char *s, int flag);
void		*lexer(char *store, t_prompt *p);
char		**cmdsubsplit(char const *s, char *set);
char 		**m_replace(char ***old, char **new, int oi);
int 		m_size(char **m);
void		m_free(char ***m);
char		**dup_node(char **av);
char 		**ex_split(char **av, t_prompt *prompt);
void 		int_var(t_str *var);
t_list  	*fillnode(char **av, int i);
void		*parsing(char **av, t_prompt *p);

t_str	*get_infile2(t_str *node, char **args, int *i);
t_str	*get_infile1(t_str *node, char **args, int *i);
t_str	*get_outfile2(t_str *node, char **args, int *i);
t_str	*get_outfile1(t_str *node, char **args, int *i);
char	*clean_trim(char *s , int singleq , int doubleq);
int		get_fd(int oldfd, char *path, int flags[2]);
int		handle_builtin(t_prompt *prompt, t_list *cmd, int *is_exit, int n);
int 	get_here_doc(char *str[2], char *aux[2]);
void 	free_content(void *content);

int cmd_exit(t_list *cmd, int *f_exit);
int	cmd_cd(t_prompt *p);
int	cmd_export(t_prompt *prompt);
int	cmd_unset(t_prompt *prompt);
void handle_int(int signum);
void *exec_cmd(t_prompt *prompt, t_list *cmd_list);
int len_count(char *s, char c);
int cmd_echo(t_list *cmd);
int	cmd_pwd(void);
int	check_builtins(t_str *s);
int	handle_builtin(t_prompt *prompt, t_list *cmd, int *is_exit, int n);
int	m_put(char **m, int nl, int fd);
void reset_signals_to_default(void);

void	*check_exec(t_prompt *prompt, t_list *cmd, int fd[2]);

#endif