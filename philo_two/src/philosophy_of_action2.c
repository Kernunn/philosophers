#include "struct.h"
#include "create_str_from_time.h"
#include "unistd.h"
#include "libft.h"
#include <stdlib.h>
#include <semaphore.h>
#include <sys/time.h>

extern sem_t **g_sem_death;
extern sem_t *g_sem_for_write;
extern long long int *g_time_last_meal;

void sleeping_and_thinking(t_data *data, int i) {
  char str[33];

  ft_create_str(str, data, i + 1, IS_SLEEPING);
  sem_wait(g_sem_for_write);
  write(1, str, ft_strlen(str));
  sem_post(g_sem_for_write);
  usleep(data->time_to_sleep * 1000);
  ft_create_str(str, data, i + 1, IS_THINKING);
  sem_wait(g_sem_for_write);
  write(1, str, ft_strlen(str));
  sem_post(g_sem_for_write);
}

void eating(t_data *data, int i) {
  char str[33];
  struct timeval time;

  ft_create_str(str, data, i + 1, IS_EATING);
  sem_wait(g_sem_for_write);
  write(1, str, ft_strlen(str));
  sem_post(g_sem_for_write);
  gettimeofday(&time, NULL);
  sem_wait(g_sem_death[i]);
  g_time_last_meal[i] = time.tv_sec * 1000000 + time.tv_usec;
  sem_post(g_sem_death[i]);
  usleep(data->time_to_eat * 1000);
}
