#ifndef ARGUMENTS_H
#define ARGUMENTS_H

int	check_argument_count(int argc);

int	fill_args(int argc, char **argv, int *args);

enum
{
	NUMBER_OF_PHILOSOPHERS = 0,
	TIME_TO_DIE = 1,
	TIME_TO_EAT = 2,
	TIME_TO_SLEEP = 3,
	NUMBER_OF_TIME_TO_EAT = 4,
};

#endif //ARGUMENTS_H
