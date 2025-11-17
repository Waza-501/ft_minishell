NAME		:=	minishell
CC			:=	cc
FLAGS		:= -g -Wall -Wextra -Werror

# Detect operating system
UNAME_S := $(shell uname -s)

# OS-specific settings for readline
ifeq ($(UNAME_S),Darwin)
    # macOS: Use Homebrew's GNU readline
    READLINE_PATH := $(shell brew --prefix readline 2>/dev/null || echo /opt/homebrew/opt/readline)
    CFLAGS += -I$(READLINE_PATH)/include
    LDFLAGS += -L$(READLINE_PATH)/lib
endif

LIBRARIES		:=	./libraries/libft/libft.a ./libraries/cd_ll/cd_ll.a\

LIBFT			:= ./libraries/libft

CDLL			:= ./libraries/cd_ll

SOURCES_DIR	:=	sources/
SOURCES		:=	lexer/lexer_list_utils.c\
				lexer/lexer_list.c\
				lexer/lexer_utils.c\
				lexer/lexer.c\
				lexer/tokeniser.c\
				commands/commands_list.c\
				commands/commands_list_utils.c\
				commands/setup_commands.c\
				parser/concatenate_strings.c\
				parser/expand_args.c\
				parser/expand_core.c\
				parser/expand_special_var.c\
				parser/expand_utils.c\
				parser/parsing_utils.c\
				parser/parsing.c\
				parser/handle_quotes.c\
				redirection/files_list_utils.c\
				redirection/files_list.c\
				redirection/handle_append.c\
				redirection/handle_heredoc.c\
				redirection/handle_input.c\
				redirection/handle_output.c\
				redirection/heredoc_utils.c\
				redirection/redirect_error.c\
				redirection/redirect.c\
				utils/copy_env.c\
				utils/error.c\
				utils/signals.c\
				utils/utils.c\
				main.c\
				data.c\
				builtins/ft_echo.c\
				builtins/ft_pwd.c\
				builtins/ft_env.c\
				builtins/ft_unset.c\
				builtins/ft_export.c\
				builtins/ft_cd.c\
				builtins/ft_export_utils.c\
				builtins/ft_export_utils2.c\
				builtins/ft_export_sort.c\
				builtins/ft_export_print.c\
				builtins/ft_exit.c\
				builtins/builtins_utils.c\
				executor/executor_bridge.c\
				executor/executor.c\
				executor/executor_utils1.c\
				executor/executor_utils2.c\
				executor/executor_utils3.c\
				executor/env_sync.c\
				printing.c\

OBJECTS_DIR	:=	objects/
OBJECTS		:=	$(addprefix $(OBJECTS_DIR), $(SOURCES:.c=.o))
HEADER_DIR	:=	headers/
HEADERS		:=	-I $(HEADER_DIR) -I ./libraries/libft

all:		libraries $(NAME)

# $(NAME):	$(OBJECTS)
# 				$(CC) $(FLAGS) -o $@ $^ -lreadline $(HEADERS) $(LIBRARIES)

# $(OBJECTS_DIR)%.o:	$(SOURCES_DIR)%.c
# 					@mkdir -p $(dir $@)
# 					$(CC) $(FLAGS) $(HEADERS) -c -o $@ $<

$(NAME):    $(OBJECTS)
				$(CC) $(FLAGS) $(LDFLAGS) -o $@ $^ -lreadline $(HEADERS) $(LIBRARIES)

$(OBJECTS_DIR)%.o:  $(SOURCES_DIR)%.c
					@mkdir -p $(dir $@)
					$(CC) $(FLAGS) $(CFLAGS) $(HEADERS) -c -o $@ $<

libraries:
			@$(MAKE) -C $(LIBFT)
			@$(MAKE) -C $(CDLL)

clean:
			@rm -f $(OBJECTS)
			@$(MAKE) -C $(LIBFT) clean
			@$(MAKE) -C $(CDLL) clean

fclean:		clean
			@rm -f $(NAME)
			@$(MAKE) -C $(LIBFT) fclean
			@$(MAKE) -C $(CDLL) fclean
			@if [ -d "$(OBJECTS_DIR)" ]; then rm -drf $(OBJECTS_DIR); fi
			@echo "$(GREEN)Cleaned up all created files.$(NO_COLOR)"

re:	fclean all

.PHONY:		all libraries clean fclean re
