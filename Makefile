NAME		:=	minishell
CC			:=	cc
FLAGS		:=	-Wall -Werror -Wextra -g -fsanitize=address

LIBRARIES		:=	./libraries/libft/libft.a ./libraries/cd_ll/cd_ll.a\

LIBFT			:= ./libraries/libft

CDLL			:= ./libraries/cd_ll

SOURCES_DIR	:=	sources/
SOURCES		:=	utils/copy_env.c\
				lexer/lexer_list_clear.c\
				lexer/lexer_list.c\
				lexer/lexer.c\
				commands/commands_list.c\
				commands/commands_list_utils.c\
				commands/setup_commands.c\
				parser/concatonate_strings.c\
				parser/concatonate_utils.c\
				parser/expand_args.c\
				parser/expand_utils.c\
				parser/handle_append.c\
				parser/handle_heredoc.c\
				parser/handle_input.c\
				parser/handle_output.c\
				parser/parsing.c\
				utils/exit_error.c\
				main.c\
				utils/signals.c\
				lexer/tokeniser.c\
				utils/utils.c\
# 				builtins/ft_cd.c\
# 				builtins/ft_echo.c\
# 				builtins/ft_pwd.c\
# 				executor/executor.c\
# 				executor/execute_ultil1.c\
# 				execute/execute_ultil2.c\

OBJECTS_DIR	:=	objects/
OBJECTS		:=	$(addprefix $(OBJECTS_DIR), $(SOURCES:.c=.o))
HEADER_DIR	:=	headers/
HEADERS		:=	-I $(HEADER_DIR)

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
			@rm -rf $(OBJECTS)
			@$(MAKE) -C $(LIBFT) clean
			@$(MAKE) -C $(CDLL) clean

fclean:		clean
			@rm -rf $(NAME)
			@$(MAKE) -C $(LIBFT) fclean
			@$(MAKE) -C $(CDLL) fclean
			@if [ -d "$(OBJECTS_DIR)" ]; then rm -drf $(OBJECTS_DIR); fi
			@echo "$(GREEN)Cleaned up all created files.$(NO_COLOR)"

re:	fclean all

.PHONY:		all libraries clean fclean re
