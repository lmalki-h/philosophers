NAME= philo_two

EXT = c
CC = gcc
CFLAGS = -Wall -Wextra -Werror
PTHREAD_LIB = -lpthread
HEADER = $(DIR_INC)/philo_two.h
RM = rm
RF = -rf

SRCS =	main.c \
		routine.c \
		free.c \
		init.c \
		print_status.c \
		eat.c \

SHARED = ft_atoi.c \
		ft_itoa.c \
		ft_usleep.c \
		time_since.c \
		get_time_in_ms.c \


SHARED_OBJS = $(addprefix $(DIR_OBJ)/, $(SHARED:.$(EXT)=.o))
OBJS = $(addprefix $(DIR_OBJ)/, $(SRCS:.$(EXT)=.o))

DIR_OBJ = obj
DIR_SHARED = ../shared
DIR_SRC = src
DIR_INC = inc

vpath %.c $(DIR_SRC):$(DIR_SHARED)

all: $(DIR_OBJ) $(OBJS) $(SHARED_OBJS) $(HEADER) $(NAME)

$(DIR_OBJ)/%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(DIR_OBJ):
	mkdir -p $(DIR_OBJ)

$(NAME): $(DIR_OBJ) $(OBJS) $(SHARED_OBJS) $(HEADER)
	$(CC) $(CFLAGS) $(OBJS)  $(SHARED_OBJS) $(PTHREAD_LIB) -o $(NAME)

clean:
	$(RM) $(RF) $(DIR_OBJ)

fclean: clean
	$(RM) $(RF) $(NAME)

re: fclean all

.PHONY: all clean fclean re
