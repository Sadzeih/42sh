##
## Makefile for wolf3d in /home/desrum_m/code/epitech/Igraph/wolf3D/MUL_2014_wolf3d
## 
## Made by Martin Desrumaux
## Login   <desrum_m@epitech.net>
## 
## Started on  Sat Dec  6 16:19:34 2014 Martin Desrumaux
## Last update Fri Jun  5 15:37:43 2015 devos_f
##

CC	=		gcc

RM	=		rm -f

NAME	=		42sh

ifeq			($(DEBUG), yes)
CFLAGS	+=		-g
#CFLAGS	+=		-Wwrite-strings
CFLAGS	+=		-Wcast-align
CFLAGS	+=		-Wstrict-prototypes
#CFLAGS	+=		-Wconversion
CFLAGS	+=		-Wunreachable-code
CFLAGS	+=		-ggdb
CFLAGS	+=		-DDEBUG=1
endif

ifeq			($(COLOR), yes)
CFLAGS	+=		-fdiagnostics-color=always
endif

CFLAGS	+=		-Wall -Wextra -pedantic
#CFLAGS	+=		-ansi -D_DEFAULT_SOURCE -D_BSD_SOURCE
CFLAGS	+=		-I include/

LDFLAGS =		-lncurses

SRCS	=		src/main.c \
			src/signal.c \
			src/lib/lib.c \
			src/lib/lib_bis.c \
			src/lib/lib_again.c \
			src/lib/lib_error.c \
			src/lib/aliases_tools.c \
			src/lib/fnlist.c \
			src/lib/get_next_line.c \
			src/lib/my_strcpy.c \
			src/my_env.c \
			src/my_env_change.c \
			src/my_cd_getcwd_listcat.c \
			src/my_cd_getcwd.c \
			src/my_cd.c \
			src/my_exit.c \
			src/my_built_in_cmd.c \
			src/my_built_in.c \
			src/echo.c \
			src/my_lexer_general.c \
			src/my_lexer_core.c \
			src/my_lexer.c \
			src/tree_create.c \
			src/path_execution.c \
			src/tree_execution.c \
			src/tree_execution_pipeline.c \
			src/tree_execution_pipeline_cmd.c \
			src/tree_execution_op.c \
			src/redir_parser.c \
			src/redir_exec.c \
			src/execution.c \
			src/cmd_check.c \
			src/local_vars/set.c \
			src/local_vars/unset.c \
			src/line_edition/edit.c \
			src/line_edition/cap.c \
			src/line_edition/add_del_char.c \
			src/line_edition/move.c \
			src/line_edition/clear.c \
			src/line_edition/move_words.c \
			src/line_edition/key_actions.c \
			src/line_edition/termcaps.c \
			src/history/history.c \
			src/history/built_in_history.c \
			src/history/built_in_history_bis.c \
			src/history/aff_history.c \
			src/history/lib_history.c \
			src/lib/fnlist_double.c \
			src/globbing/glob_check.c \
			src/globbing/glob_funct.c \
			src/globbing/glob_main.c \
			src/globbing/dlist_to_tab.c \
			src/history/move_in_history.c \
			src/aliases/exec_alias.c \
			src/aliases/alias.c \
			src/aliases/unalias.c

OBJS	=		$(SRCS:.c=.o)

all :			$(NAME)

$(NAME) :		$(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean :
	$(RM) $(OBJS)

fclean :		clean
	$(RM) $(NAME)

re :			fclean $(NAME)
