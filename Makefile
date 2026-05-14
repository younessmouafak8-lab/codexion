NAME = codexion
C_FLAGS = -Wall -Wextra -Werror -pthread 
# -fsanitize=thread
C_HEADER = codexion.h
RM = rm -rf
SRCS = main.c ft_atoi.c parsing.c dongles_utils.c monitor_utils.c thread_routine.c pre_launch_utils.c cleanup_utils.c heap.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME) : $(OBJS) $(C_HEADER)
	cc $(C_FLAGS) $(OBJS) -o $(NAME)

%.o: %.c $(C_HEADER)
	cc $(C_FLAGS) -c $<

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all