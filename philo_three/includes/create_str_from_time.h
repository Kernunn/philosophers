#	ifndef PHILOSOPHERS_CREATE_STR_FROM_TIME_H
#	define PHILOSOPHERS_CREATE_STR_FROM_TIME_H

#include "struct.h"

void ft_create_str(char *str, t_data *data, int i, int option);

#define TAKE_FORK 0
#define IS_EATING 1
#define IS_SLEEPING 2
#define IS_THINKING 3
#define IS_DIED 4

#	endif
