
#program ------------------------------------------
NAME = minishell

#source directories
SRCS =	./srcs/init.c \
		./srcs/minishell.c \
		./srcs/pending.c \
		./srcs/utils.c \
		./srcs/parsing/commands/build_commands_utils.c \
		./srcs/parsing/tokens/token_split_utils.c \
		./srcs/parsing/tokens/token_parsing_utils.c \
		./srcs/parsing/commands/build_commands.c \
		./srcs/parsing/commands/command_list.c \
		./srcs/parsing/tokens/token_parsing.c \
		./srcs/parsing/tokens/substitutions.c \
		./srcs/parsing/tokens/redirections.c \
		./srcs/parsing/tokens/line_parsing.c \
		./srcs/parsing/tokens/token_split.c \
		./srcs/parsing/tokens/linked_list.c \
		./srcs/parsing/term_attributes.c \
		./srcs/parsing/signals.c \
		./srcs/parsing/parsing.c \
		./srcs/parsing/error.c \
		./srcs/exec/exec_utils.c \
		./srcs/exec/exec.c \
		./srcs/exec/path.c \
		./srcs/builtins/builtins_utils.c \
		./srcs/builtins/export_builtin.c \
		./srcs/builtins/builtins.c \
		./srcs/cleaning.c \
		./srcs/errors/error_handling.c \
				

#colours ------------------------------------------
B_BLUE='\033[1;34m'
RED=\033[0;31m
YELLOW=\033[33m
MAGENTA=\033[35m
B_GREEN=\033[1;32m
PURPLE=\033[1;35m
COLOUR_END=\033[0m

#object directories and compilation instructions ----------
OBJS = $(SRCS:.c=.o)
.SILENT: $(OBJS)
CC = gcc
CFLAGS = -g -Wall -Wextra #-Werror
RM = rm -fr
LIBS = ./includes/libft/libft.a ./includes/readline/libreadline.a ./includes/readline/libhistory.a -lreadline -lcurses

$(NAME): $(OBJS)
	@$(MAKE) -C ./includes/libft
	# --@cd ./includes/readline && ./configure
	# @$(MAKE) everything -C ./includes/readline
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS)
	@echo "$(YELLOW)⚡️$(NAME) ⚡️$(B_GREEN)has been created $(COLOUR_END)!"

#rules ------------------------------------------
all: $(NAME)

clean:
	@$(MAKE) clean -C ./includes/libft
	@$(RM) $(OBJS)
	@$(RM) $(ODIR)
	@echo "🧹"

fclean: clean
	@$(MAKE) fclean -C ./includes/libft
	@$(RM) $(NAME)
	@echo "$(RED)$(NAME) has been deleted 🗑️$(COLOUR_END)"

rclean:
	@$(MAKE) clean -C ./includes/readline

re: fclean all

.PHONY: all clean fclean rclean re