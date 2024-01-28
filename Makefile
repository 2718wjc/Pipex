NAME = pipex
LIBDIR = ./libft/
LIBNAME = ft
LIB = $(LIBDIR)lib$(LIBNAME).a
INCDIRS = ./

MAKE = make
CC = cc
AR = ar
CFLAGS = -Wall -Wextra -Werror $(foreach D, $(INCDIRS), -I$(D))
ARFLAGS = rs

SRCS = pipex_main.c pipex_heredoc.c pipex_utils.c
SRCS_B = pipex_main_bonus.c pipex_heredoc_bonus.c pipex_utils_bonus.c

OBJS = $(SRCS:c=o)
OBJS_B = $(SRCS_B:c=o)

all: $(NAME)

$(NAME): LAST_ALL

bonus: LAST_BONUS

LAST_ALL: $(OBJS) $(LIB)
	rm -f LAST_BONUS
	$(CC) -o $(NAME) $(OBJS) -L$(LIBDIR) -l$(LIBNAME)
	touch $@

LAST_BONUS: $(OBJS_B) $(LIB)
	rm -f LAST_ALL
	$(CC) -o $(NAME) $(OBJS_B) -L$(LIBDIR) -l$(LIBNAME)
	touch $@

$(LIB):
	$(MAKE) -C $(LIBDIR) all

%.o: %.c $(foreach D, $(INCDIRS), $(D)*.h)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(OBJS_B) LAST_ALL LAST_BONUS
	$(MAKE) -C $(LIBDIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBDIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus
