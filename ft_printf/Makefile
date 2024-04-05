
NAME = libftprintf.a

ROOT = ./
SRCSPATH = ./src/
LIBFTPATH = ./libft/
INCPATH = ./includes/ ./libft/

SRCS = $(wildcard $(SRCSPATH)*.c)
OBJS = $(patsubst %.c, %.o,$(SRCS))

LIBFT = $(LIBFTPATH)*.o

CC = cc
CFLAGS = -Wall -Wextra -Werror -c $(foreach H,$(INCPATH),-I$(H))

all : $(NAME)

$(NAME) : $(LIBFT) $(OBJS)
	ar -rcs $(NAME) $(LIBFT) $(OBJS)

$(LIBFT) :
	make -C $(LIBFTPATH) all

%.o : %.c
	$(CC) $(CFLAGS) $< -o $@

clean :
	make -C $(LIBFTPATH) clean
	rm -f $(OBJS) $(DEPS)

fclean : clean
	make -C $(LIBFTPATH) fclean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re

