NAME =	philo


SRC_PATH =	src/

SRC =\
	philosopher/destroy_philosopher.c	\
	philosopher/init_philosophers.c		\
\
	philosopher_routine/no_philosopher_died.c	\
	philosopher_routine/philosopher_eats.c		\
	philosopher_routine/philosopher_routine.c	\
	philosopher_routine/philosopher_sleeps.c	\
	philosopher_routine/print_state_change.c	\
	philosopher_routine/sleep_till.c			\
\
\
	run_philosophers/monitor.c			\
	run_philosophers/run_philosopher.c	\
\
\
	tools/atoll.c		\
	tools/isdigit.c		\
	tools/isspace.c		\
	tools/putstr_fd.c	\
	tools/strlen.c		\
\
\
	arguments.c			\
	main.c				\
	time.c



DIR_INCS =\
	include/	\
	include/tools


INCLUDES =\
	$(addprefix -I , $(DIR_INCS))


LIBS =\
	-lpthread


DIR_BUILD =		.build/
OBJS =			$(patsubst %.c, $(DIR_BUILD)%.o, $(SRC))
DEPS =			$(patsubst %.c, $(DIR_BUILD)%.d, $(SRC))
DEPS_FLAGS =	-MMD -MP
CFLAGS =		-Wall -Wextra -Werror -O3 #-fsanitize=thread -g3
RM =			rm -rf
AR =			ar rcs


.PHONY:		all
all:
			$(MAKE) $(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBS) -o $(NAME)

.PHONY:	bonus
bonus:	all

.PHONY:	clean
clean:
		$(RM) $(DIR_BUILD)

.PHONY:	fclean
fclean:	clean
		$(RM) $(NAME)

.PHONY:	re
re:		fclean
		$(MAKE) all

-include $(DEPS)

$(DIR_BUILD)%.o : $(SRC_PATH)%.c
		@mkdir -p $(shell dirname $@)
		$(CC) $(CFLAGS) $(DEPS_FLAGS) $(INCLUDES) -c $< -o $@
