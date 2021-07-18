#	ifndef STRUCT_H
#	define STRUCT_H

#include "pthread.h"
#include <semaphore.h>

typedef struct s_data {
  int number_of_philosos;
  int time_to_die;
  int time_to_eat;
  int time_to_sleep;
  int number_of_times_each_philo_must_eat;
  int all_count_meal;
  long long int begin_time;
} t_data;

typedef struct s_args {
  int number_of_the_philosopher;
  t_data *data;
} t_args;

#	endif
