NAME		:=	minishell
CC			:=	cc
FLAGS		:=	-Wall -Wextra -g -fsanitize=address -lreadline

LIBRARIES		:=	./libraries/libft/libft.a ./libraries/cd_ll/cd_ll.a\

LIBFT			:= ./libraries/libft

CDLL			:= ./libraries/cd_ll

SOURCES_DIR	:=	sources/
SOURCES		:=	lexer_list.c\
				lexer.c\
				main.c\
				parsing.c\
				signals.c\
				tokeniser.c\
				utils.c\

OBJECTS_DIR	:=	objects/
OBJECTS		:=	$(addprefix $(OBJECTS_DIR), $(SOURCES:.c=.o))
HEADER_DIR	:=	headers/
HEADERS		:=	-I $(HEADER_DIR)

all:		libraries $(NAME)

$(NAME):	$(OBJECTS)
				$(CC) $(FLAGS) -o $@ $^ $(HEADERS) $(LIBRARIES)

$(OBJECTS_DIR)%.o:	$(SOURCES_DIR)%.c
					@mkdir -p $(dir $@)
					$(CC) $(FLAGS) $(HEADERS) -c -o $@ $<

libraries:	
			$(MAKE) -C $(LIBFT)
			$(MAKE) -C $(CDLL)

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
