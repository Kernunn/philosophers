#include "struct.h"
#include "create_str_from_time.h"
#include "unistd.h"
#include "libft.h"
#include <stdlib.h>
#include <semaphore.h>
#include <sys/time.h>

void sleeping_and_thinking(t_data *data, int i) {
  char str[33];

  ft_create_str(str, data, i + 1, IS_SLEEPING);
  sem_wait(data->sem_for_write);
  write(1, str, ft_strlen(str));
  sem_post(data->sem_for_write);
  usleep(data->time_to_sleep * 1000);
  ft_create_str(str, data, i + 1, IS_THINKING);
  sem_wait(data->sem_for_write);
  write(1, str, ft_strlen(str));
  sem_post(data->sem_for_write);
}

void eating(t_data *data, int i) {
  char str[33];
  struct timeval time;

  ft_create_str(str, data, i + 1, IS_EATING);
  sem_wait(data->sem_for_write);
  write(1, str, ft_strlen(str));
  sem_post(data->sem_for_write);
  gettimeofday(&time, NULL);
  sem_wait(data->sem_death[i]);
  data->time_last_meal = time.tv_sec * 1000000 + time.tv_usec;
  sem_post(data->sem_death[i]);
  usleep(data->time_to_eat * 1000);
}
