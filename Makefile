NAME = codexion
C_FLAGS = -Wall -Wextra -Werror -pthread 
C_HEADER = coders/codexion.h
RM = rm -rf
SRCS = coders/main.c coders/ft_atoi.c coders/parsing.c coders/dongles_utils.c coders/monitor_utils.c coders/thread_routine.c \
		coders/pre_launch_utils.c coders/cleanup_utils.c coders/heap.c coders/thread_utils.c coders/thread_actions.c coders/heap_utils.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME) : $(OBJS) $(C_HEADER)
	cc $(C_FLAGS) $(OBJS) -o $(NAME)

coders/%.o: coders?%.c $(C_HEADER)
	cc $(C_FLAGS) -c $<

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all