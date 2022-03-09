/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snovaes <snovaes@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 17:26:00 by hde-camp          #+#    #+#             */
/*   Updated: 2022/03/09 20:41:58 by snovaes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <libft.h>
# include <errno.h>
# include <fcntl.h>

# define RESET "\001\033[0m\002"
# define RED "\001\033[41;1;37m\002"
# define YELLOW "\001\033[1;33m\002"

enum e_word_type{
	UNKNOWN = 0,
	SIMPLE = 1,
	OPERATOR = 2,
	VARIABLE = 3,
	D_LESSTHAN = 4,
	D_GREATERTHAN = 5,
	WHITE_SPACE = 6,
	D_QUOTED = 34,
	S_QUOTED = 39,
	S_LESSTHAN = 60,
	S_GREATERTHAN = 62,
	PIPE = 124
};

enum e_cmd_type{
	UNDEFINED = 0,
	BUILTIN = 1,
	FILE_ = 2,
	BIN = 3,
	INVALID_BIN = 4,
	INVALID = 5,
	VAR_DECLARATION = 6,
	HEREDOC = 7,
	UNEXPECTED_TOKEN = 8
};

typedef struct s_shstate
{
	char				*input;
	int					keep_alive;
	int					exit_code;
	t_dl_list			*words;
	t_dl_list			*var_list;
	t_dl_list			*cmds;
}	t_shstate;

typedef struct s_cmd
{
	char				**argv;
	enum e_word_type	l_operator;
	enum e_word_type	r_operator;
	enum e_cmd_type		type;
	int					write;
	int					read;
	int					p_id;
	int					exit_status;
	char				*err_msg;
}	t_cmd;

typedef struct s_word
{
	const char			*start;
	char				*expanded;
	int					size;
	int					expanded_size;
	enum e_word_type	type;
}	t_word;

typedef struct s_variable
{
	char	*key;
	char	*value;
	int		exported;
}	t_variable;

char		**load_paths(t_shstate *state);
void		input_parser(t_shstate *state);
void		word_delimiter(t_word **word);
t_variable	*create_var(const char *key, const char *value);
void		delete_var(void *var);
void		update_var(t_variable *var, const char *new_value);
const char	*get_var_value(t_shstate *state, char *name);
t_variable	*get_variable(t_shstate *state, const char *name);
void		set_var(t_shstate *state, const char *name, const char *value);
void		unset_var(t_dl_list *var_item);
void		unset_all_var(t_shstate *state);
void		print_env(t_shstate *state);
void		load_state(t_shstate *state);
void		unload_state(t_shstate *state);
void		expand_words(t_shstate *state);
void		expand_sub_words(t_shstate *state, t_dl_list *sub_words);
t_dl_list	*build_quoted_sub_words(t_word **word);
void		sub_d_quoted_delimiter(t_word **word);
void		sub_s_quoted_delimiter(t_word **word);
void		sub_simple_delimiter(t_word **word);
void		free_word_list(t_shstate *state);
t_dl_list	*build_sub_words(t_word **word);
t_dl_list	*build_quoted_sub_words(t_word **word);
t_dl_list	*build_simple_sub_words(t_word **word);
void		free_word(void *wrd);
void		merge_words(t_shstate *state);
void		build_cmds(t_shstate *state);
void		free_cmds(t_shstate *state);
void		eval_cmds(t_shstate *state);
int			**allocate_pipes(t_dl_list *cmd_lst);
void		close_free_pipes(int **pipes);
void		execute_cmds(t_shstate *state);
void		set_file_redirections(t_cmd *cmd);
void		set_pipe_redirections(t_dl_list *cmd_lst, int **pipes, int *i);
void		execute_cmd(t_shstate *state, t_dl_list *cmd_lst);
void		set_cmd_input(t_dl_list *current);
void		set_cmd_output(t_dl_list *current);
void		validate_syntax(t_cmd	*cmd, t_shstate	*state);
int			check_file(char	*filename, int print_errors);
int			check_relative_file(t_cmd *cmd, char **paths);
void		define_cmd_type(t_cmd *cmd);
void		operator_word_delimiter(t_word **word);
t_cmd		*get_cmd_and_move(t_dl_list **words);
void		builtin_exit(t_shstate *state, t_cmd	*cmd);
void		builtin_echo(t_cmd *cmd);
void		builtin_pwd(void);
void		builtin_env(t_shstate *state);
void		builtin_unset(t_shstate *state, t_cmd *cmd);
int			eval_var_atribution(char *name);
int			eval_varname(char *name);
void		builtin_export(t_shstate *state, t_cmd *cmd);
void		builtin_cd(t_shstate *state, t_cmd *cmd);
char		**get_state_env(t_shstate *state);
char		**split_in_two(char *str);
void		set_shell_handlers(void);
void		set_child_handlers(int cpid);
void		heredoc(t_cmd	*cmd);
void		close_io(t_cmd *cmd);
t_cmd		*new_cmd(void);
void		split_cmd_in_two(t_dl_list	*cmd_list);
void		validate_file_sintax(t_cmd	*cmd);
void		r_trim(char *str);
char		get_last(char	*str);
void		exec_input(t_shstate *state);
char		*get_input(void);
int			input_is_incomplete(char *ptr);
void		free_str_vector(char **vector);
int			cmd_list_should_run(t_dl_list	*cmds);
void		execute_heredocs(t_shstate *state);
void		print_welcome_msg(void);
void		print_error(void);

#endif