NAME	:=	philo

SRCS	:=	./srcs/main.c \
			./srcs/ft_atoi.c \
			./srcs/philo.c \
			./srcs/mutex.c \
			./srcs/monitoring.c \
			./srcs/time.c \
			./srcs/utils.c

OBJS = ${SRCS:%.c=%.o}

FLAGS	:=	-Wall -Werror -Wextra -pthread

HEADER	:=	./includes/philo.h

all: $(NAME)

%.o: %.c $(HEADER)
	@echo "Compiling ${notdir $<}"
	@$(CC) -c $(CFLAGS) -I includes -o $@ $<

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) $(OBJS) -o $(NAME)
	@echo "Success!"

clean:
	@echo "Cleaning"
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

# -g -fsanitize=thread