NAME = libft.a
FTPFDIR = ./ft_printf/
GNLDIR = ./GNL/
INCDIRS = ./ $(FTPFDIR) $(GNLDIR)

CC = cc
AR = ar
CFLAGS = -Wall -Wextra -Werror $(foreach D, $(INCDIRS), -I$(D))
ARFLAGS = rs

SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	   ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
	   ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
	   ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
	   ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
	   ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
	   ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_lstnew.c \
	   ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
	   ft_lstclear.c ft_lstiter.c ft_lstmap.c ft_lstswap.c ft_strdup_s.c \
	   ft_lstnew_s.c ft_split_quot.c

SRCS_FTPF = ft_printf.c prs.c utils.c truncstr.c add_pads.c prnt.c
SRCS_GNL = get_next_line.c get_next_line_utils.c

SRCS += $(foreach D, $(SRCS_FTPF), $(FTPFDIR)$(D)) \
		$(foreach D, $(SRCS_GNL), $(GNLDIR)$(D))

OBJS = $(SRCS:c=o)

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $^

%.o: %.c $(foreach D, $(INCDIRS), $(D)*.h)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
