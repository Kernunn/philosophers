#include "struct.h"
#include "create_str_from_time.h"
#include "unistd.h"
#include "libft.h"
#include <sys/time.h>

extern pthread_mutex_t **restrict
g_death;
extern pthread_mutex_t *restrict
g_mutex_write;
extern long long int *g_time_last_meal;

void sleeping_and_thinking(t_data *data, int i) {
  char str[40];

  pthread_mutex_lock(g_mutex_write);
  ft_create_str(str, data, i + 1, IS_SLEEPING);
  write(1, str, ft_strlen(str));
  pthread_mutex_unlock(g_mutex_write);
  usleep(data->time_to_sleep * 1000);
  pthread_mutex_lock(g_mutex_write);
  ft_create_str(str, data, i + 1, IS_THINKING);
  write(1, str, ft_strlen(str));
  pthread_mutex_unlock(g_mutex_write);
}

void eating(t_data *data, int i) {
  char str[40];
  struct timeval time;

  pthread_mutex_lock(g_mutex_write);
  ft_create_str(str, data, i + 1, IS_EATING);
  write(1, str, ft_strlen(str));
  pthread_mutex_unlock(g_mutex_write);
  pthread_mutex_lock(g_death[i]);
  gettimeofday(&time, NULL);
  g_time_last_meal[i] = time.tv_sec * 1000000 + time.tv_usec;
  pthread_mutex_unlock(g_death[i]);
  usleep(data->time_to_eat * 1000);
}
