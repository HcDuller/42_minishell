NAME		=	minishell

CC			=	gcc
AR			=	ar -rc
RM			=	rm -rfd
CFLAGS		=	-Wall -Wextra -Werror -g

SRC_DIR		=	src
OBJ_DIR		=	obj
I_DIR		=	includes
L_DIR		=	libs
LIBS		=	-lft -lreadline

SRC_CODE	=	main.c \
				load_paths.c \
				input_parser.c \
				input_exec.c \
				word_delimiter.c \
				expand_words.c \
				get_var.c \
				var_crud.c \
				set_var.c \
				unset_var.c \
				print_env.c \
				state_management.c \
				get_state_env.c \
				sub_word_delimiters.c \
				sub_word_builders.c \
				merge_words.c \
				expand_sub_words.c \
				build_cmds.c \
				eval_cmds.c \
				eval_varname.c \
				valid_cmds.c \
				free_words.c \
				free_cmds.c \
				pipe_handlers.c \
				execute_cmds.c \
				execute_cmd.c \
				get_cmd_and_move.c \
				set_redirections.c \
				set_cmd_io.c \
				validate_syntax.c \
				validate_file_syntax.c \
				file_checkers.c \
				define_cmd_type.c \
				operator_word_delimiter.c \
				builtin_echo_exit.c \
				builtin_pwd.c \
				builtin_export.c \
				builtin_env.c \
				builtin_unset.c \
				builtin_cd.c \
				sig_handling.c \
				heredoc.c \
				print_word_cmds.c \
				split_in_two.c \
				split_cmd_in_two.c \
				free_str_vector.c \
				execute_heredoc.c \
				welcome_msg.c \

# ============================================================================ #
#                                   COLOR                                      #
# ============================================================================ #

CL_BOLD	 = \e[1m
CL_DIM	= \e[2m
CL_UDLINE = \e[4m

NO_COLOR = \e[0m

BG_TEXT = \e[48;2;45;55;72m
BG_BLACK = \e[48;2;30;31;33m

FG_WHITE = $(NO_COLOR)\e[0;37m
FG_TEXT = $(NO_COLOR)\e[38;2;189;147;249m
FG_TEXT_PRIMARY = $(NO_COLOR)$(CL_BOLD)\e[38;2;255;121;198m

LF = \e[1K\r$(NO_COLOR)
CRLF= \n$(LF)

# ============================================================================ #

SRC			=	$(addprefix $(SRC_DIR)/,$(SRC_CODE))
OBJS		=	$(addprefix $(OBJ_DIR)/,$(SRC_CODE:.c=.o))

.PHONY: clean fclean re

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS) ./$(L_DIR)/libft.a
	$(CC) $(OBJS) -I $(I_DIR) -L $(L_DIR) $(LIBS) -o $(NAME)
	@printf "$(LF)🎉 $(FG_TEXT)Successfully Created $(FG_TEXT_PRIMARY)$@!$(FG_TEXT)\n$(NO_COLOR)"

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(I_DIR)

./$(L_DIR)/libft.a:
	make -C ./libs/libft
	cp -f ./libs/libft/libft.a ./$(L_DIR)
	cp -f ./libs/libft/libft.h ./$(I_DIR)
	@printf "$(LF)🚀 $(FG_TEXT)Successfully Created $(FG_TEXT_PRIMARY)$@'s Object files$(FG_TEXT)!\n$(NO_COLOR)"

clean:
	$(RM) $(NAME) $(OBJ_DIR)
	make clean -C ./$(L_DIR)/libft
	@printf "$(LF)🧹 $(FG_TEXT)Cleaning $(FG_TEXT_PRIMARY)$(NAME)'s Object files...\n"

fclean: clean
	$(RM) $(NAME) ./$(L_DIR)/*.a
	@printf "$(LF)🧹 $(FG_TEXT)Cleaning $(FG_TEXT_PRIMARY)$(NAME)\n$(NO_COLOR)"

re: fclean all