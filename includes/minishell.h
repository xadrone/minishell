/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgyles <jgyles@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 21:25:37 by jgyles            #+#    #+#             */
/*   Updated: 2022/02/21 17:34:55 by jgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../Libft/libft.h"
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_env
{
	char			*key;
	char			*sep;
	char			*value;
	int				pos;
	struct s_env	*next;
}	t_env;

typedef struct s_redir
{
	// char			*cmd;
	char			*filename;
	int				cmd_count;
	int				type;
	int				in;
	int				out;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmds
{
	char			*cmd;
	char			**args;
	int				flag;
	t_redir			*redirect;
	struct s_cmds	*next;
}	t_cmds;

typedef struct s_all
{
	t_env	**env;
	t_cmds	*cmd;
	int		cmd_count;
	int		err;
	char	**envp;
}	t_all;

/*check_syntax*/
void 	skip_spaces(char **line);
int		wrong_pipe(char *line);
int		double_semicolon(char *line);
int		wrong_semicolon(char *line);
char	*first_redirect(char *line);
char	*wrong_redirects(char *line);
int		empty_redirects(char *line);
char	*search_err(char *line);
char	*check_quot(char *line);

/*parcer*/
int		check_syntax(char *line, t_all *data);
int		parser(char *line, t_all *data);

/*env_parser*/
void	add_env(char *env, t_env **envp);
void	parse_env(char **env, t_all *data);
t_env	*init_elem(char *key, char *sep, char *val);
// void	print_env(t_env **data, char *flag);
void	add_elem(t_env **head, t_env *elem);

/*init_struct*/
t_env	**init_env();
void	init_struct(t_all **data);

/*line_handler*/
char	*replace_env(char *line, int start, char *key, char *value);
char	*get_env(char *line, t_env *env, int *i);
void	quotes_handler(char *line, int *i);
void	remove_double_quotes(char *line, int *i);
char	*double_quotes_handler(char *line, int *i, t_all *data);

/*err_handler*/
char	*return_err(char *line, int *i, t_all *data);

/*buildins*/
void	env_buildin(t_env **envp);
int		pwd_buildin(void);
void	export_buildin(t_all *data, char **args);
int		unset(t_all *data, char **args);
int		cd_buildin(char **args);
void	echo_buildin(char **args);
void	ft_putstr(char *str);

/*sort_env*/
char	*find_next(char **keys, t_env **env, int i);
char	*find_last(t_env **env);
char	*find_first(t_env **env);
void	export_output(char **keys, t_env **env);
int		is_more(char *str1, char *str2);
char	**set_array(t_env **env, int *count);

/*redirect_parse*/
char	*parse_redir(char *line, int *i, t_all *data);
t_redir	*add_redir(char *line, int *i, t_all *data);
char	*set_cmd(char *line, int i);

/*shlvl*/
void	increment(t_env *envp);
void	shlvl_increment(t_env *envp);

/*executor*/
void	executor(t_all *data);
void	set_flag(t_cmds *cmd);

/*envp_array*/
char	**create_array_envp(char **envp);
int		count_str(char **envp);

/*parse_cmd*/
char	**cmd_split(char **array, t_cmds *cmd);
char	**check_redir(char **array);
int		count_elems(char **args);
int		is_redirect(char ch);

/*split_with_quotes*/
char	**split_with_quotes(char const *s, char c);


#endif
