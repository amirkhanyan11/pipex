NAME = pipex

SRCSPATH = ./src/
PRINTFPATH = ./ft_printf/
INCPATH = ./includes/ ./ft_printf/includes/

SRCS = $(wildcard $(SRCSPATH)*.c)
OBJS = $(patsubst %.c, %.o, $(SRCS))
PRINTF = $(PRINTFPATH)libftprintf.a

CC = cc
DEBUG = -fsanitize=address
WFLAGS = -Wall -Wextra -Werror
CFLAGS = $(foreach H,$(INCPATH),-I$(H)) $(DEBUG)

all : $(NAME)

$(NAME) : $(PRINTF) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(PRINTF) -o $@

$(PRINTF) :
	make -C $(PRINTFPATH) all

$(SRCSPATH)%.o : $(SRCSPATH)%.c Makefile # idk
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	make -C $(PRINTFPATH) clean
	rm -f $(OBJS)

fclean : clean
	make -C $(PRINTFPATH) fclean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re

