NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -f

SRC = philo.c	helper.c initialize_data.c	creat_thread.c	take_actions.c

OBJECT = $(SRC:.c=.o)

%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJECT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECT)

clean:
	@ $(RM) $(OBJECT)

# d: all clean 
# 	clear
# 	valgrind --tool=helgrind --tool=drd ./philo 4 310 200 100
	
fclean: clean
		@ $(RM) $(NAME)

re: clean all

.PHONY: all clean fclean re

.SECONDARY: $(OBJECT)
# .INTERMEDIATE: $(OBJECT)