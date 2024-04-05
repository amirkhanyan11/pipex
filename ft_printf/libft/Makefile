NAME = libft.a
CC = cc
INCPATH = ../includes/
CFLAGS = -Wall -Wextra -Werror -c $(foreach H,$(INCPATH),-I$(H))


MANDATORY = ./*.c



OBJS = $(MANDATORY:.c=.o)


.PHONY :  all clean fclean re so bonus

all : $(NAME)

$(NAME) : $(OBJS)
	ar -rcs $(NAME) $(OBJS)

$(OBJS) : $(MANDATORY)
	$(CC) $(CFLAGS) $(MANDATORY)


clean :
	rm -f $(OBJS) $(BONUS_OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all
