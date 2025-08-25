NAME		:=	cd_ll.a
CC			:=	cc
FLAGS		:=	-Wall -Werror -Wextra

SOURCES_DIR	:=	sources/
SOURCES		:=	cd_ll_addback.c\
				cd_ll_addfront.c\
				cd_ll_del_list.c\
				cd_ll_del_node.c\
				cd_ll_get_node.c\
				cd_ll_init_list.c\
				cd_ll_new_node.c\
				cd_ll_utils.c\

OBJECTS_DIR	:=	objects/
OBJECTS		:=	$(addprefix $(OBJECTS_DIR), $(SOURCES:.c=.o))
HEADER_DIR	:=	headers/
HEADERS		:=	-I $(HEADER_DIR)

all:		$(NAME)

$(NAME):	$(OBJECTS)
				@ar rcs $@ $^

$(OBJECTS_DIR)%.o:	$(SOURCES_DIR)%.c
					@mkdir -p $(dir $@)
					$(CC) $(FLAGS) $(HEADERS) -c -o $@ $<

clean:
			@rm -rf $(OBJECTS)

fclean:		clean
			@rm -rf $(NAME)
			@if [ -d "$(OBJECTS_DIR)" ]; then rm -drf $(OBJECTS_DIR); fi
			@echo "$(GREEN)Cleaned up all created files.$(NO_COLOR)"

re:	fclean all

.PHONY:		all clean fclean re