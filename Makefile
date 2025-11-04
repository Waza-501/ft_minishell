NAME		:=	minishell
CC			:=	cc
FLAGS		:=	-g -fsanitize=address

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
				parser/concatonate_strings.c\
				parser/expand_args.c\
				parser/expand_utils.c\
				parser/parsing.c\
				parser/strip_quotes.c\
				redirection/handle_append.c\
				redirection/handle_heredoc.c\
				redirection/handle_input.c\
				redirection/handle_output.c\
				redirection/redirect_utils.c\
				redirection/files_list.c\
				utils/copy_env.c\
				utils/error_print.c\
				utils/error.c\
				utils/signals.c\
				utils/utils.c\
				main.c\
				builtins/ft_echo.c\
				builtins/ft_pwd.c\
				builtins/ft_env.c\
				builtins/ft_unset.c\
				executor/executor_bridge.c\
				executor/executor.c\
				executor/executor_ultil1.c\
				executor/executor_ultis2.c\

OBJECTS_DIR	:=	objects/
OBJECTS		:=	$(addprefix $(OBJECTS_DIR), $(SOURCES:.c=.o))
HEADER_DIR	:=	headers/
HEADERS		:=	-I $(HEADER_DIR) -I ./libraries/libft

all:		libraries $(NAME)

$(NAME):	$(OBJECTS)
				$(CC) $(FLAGS) -o $@ $^ -lreadline $(HEADERS) $(LIBRARIES)

$(OBJECTS_DIR)%.o:	$(SOURCES_DIR)%.c
					@mkdir -p $(dir $@)
					$(CC) $(FLAGS) $(HEADERS) -c -o $@ $<

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
