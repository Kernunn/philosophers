#	ifndef STRUCT_H
#	define STRUCT_H

#include "pthread.h"
#include <semaphore.h>

typedef struct s_data {
  int number_of_philosos;
  int time_to_die;
  int time_to_eat;
  int time_to_sleep;
  int number_of_times_each_philosopher_must_eat;
  pid_t *pid;
  sem_t *sem_for_get;
  sem_t *sem_forks;
  sem_t *sem_for_write;
  sem_t *sem_for_stop;
  sem_t *sem_for_died;
  sem_t **sem_death;
  long long int begin_time;
  long long int time_last_meal;
  pthread_t tid1;
  pthread_t tid2;
} t_data;

typedef struct s_args {
  int number_of_the_philosopher;
  t_data *data;
} t_args;

#	endif
