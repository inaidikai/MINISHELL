/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:13:03 by inkahar           #+#    #+#             */
/*   Updated: 2024/09/05 15:29:36 by inkahar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <unistd.h>

extern int	g_sig;

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
}			t_errorcode;

# define READ_END 0
# define WRITE_END 1

typedef struct s_prompt
{
	t_list	*cmds;
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

char		**m_env(char **m);
t_prompt	prepare_variables(t_prompt prompt, char *str, char **argv);

char		**mini_setenv(char *var, char *value, char **envp, int n);
char		*mini_getenv(char *var, char **envp, int n);
char		**m_exdup(char **in, char *newstr);
int			ft_strchr_i(const char *s, int c);
// char 		*expand_val(char *str, int i, int fq[2], t_prompt *prompt);
// char 		*expand_tilde(char *str, int i, int fq[2], char *home_dir);
void		*errno(t_errorcode OPCODE, char *s, int flag);
void		*lexer(char *store, t_prompt *p);
char		**cmdsubsplit(char const *s, char *set);
char		**m_replace(char ***big, char **small, int n);
int			m_size(char **m);
void		m_free(char ***m);
char		**m_dup(char **m);
// char 		**ex_split(char **av, t_prompt *prompt);
t_str		*int_var(void);
t_list		*fill_nodes(char **args, int i);
void		*parsing(char **av, t_prompt *p);

t_str		*get_infile2(t_str *node, char **args, int *i);
t_str		*get_infile1(t_str *node, char **args, int *i);
t_str		*get_outfile2(t_str *node, char **args, int *i);
t_str		*get_outfile1(t_str *node, char **args, int *i);
char		*clean_trim(char *s, int singleq, int doubleq);
int			get_fd(int oldfd, char *path, int flags[2]);
int			handle_builtin(t_prompt *prompt, t_list *cmd, int *is_exit, int n);
int			get_here_doc(char *str[2], char *aux[2]);
void		free_content(void *content);
void		rl_replace_line(const char *s, int c);

int			cmd_exit(t_list *cmd, int *f_exit);
int			cmd_cd(t_prompt *p);
int			cmd_export(t_prompt *prompt);
int			cmd_unset(t_prompt *prompt);
void		handle_int(int signum);
void		*exec_cmd(t_prompt *prompt, t_list *cmd_list);
int			len_count(char *s, char c);
int			cmd_echo(t_list *cmd);
int			cmd_pwd(void);
int			check_builtins(t_str *s);
void		child_builtin(t_prompt *prompt, t_str *n, int l, t_list *cmd);
int			handle_builtin(t_prompt *prompt, t_list *cmd, int *is_exit, int n);
int			m_put(char **m, int nl, int fd);
void		reset_signals_to_default(void);
char		*mini_getprompt(void);
void		*check_exec(t_prompt *prompt, t_list *cmd, int fd[2]);

char		*expand_path(char *str, int i, int quotes[2], char *var);
char		*expand_vars(char *str, int i, int quotes[2], t_prompt *prompt);
char		**ex_split(char **args, t_prompt *prompt);
int			ft_strchars_i(const char *s, char *set);
void		free_env(t_prompt *p);

#endif