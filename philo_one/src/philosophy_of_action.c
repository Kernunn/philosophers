#include <pthread.h>
#include "struct.h"
#include <unistd.h>
#include "libft.h"
#include "create_str_from_time.h"

extern pthread_mutex_t **restrict
g_death;
extern pthread_mutex_t **restrict
g_forks;
extern pthread_mutex_t *restrict
g_mutex_write;
extern pthread_mutex_t *restrict
g_mutex_state;
extern long long int *g_time_last_meal;
extern t_state *g_state;

void test(t_data *data, int i) {
  int n;

  n = data->number_of_philosos;
  if (g_time_last_meal[(i + n - 1) % n] < g_time_last_meal[i] ||
	  g_time_last_meal[(i + 1) % n] < g_time_last_meal[i])
	return;
  if (g_state[i] == HUNGRY && g_state[(i + n - 1) % n] != EATING
	  && g_state[(i + 1) % n] != EATING) {
	g_state[i] = EATING;
	pthread_mutex_unlock(g_forks[i]);
  }
}

void take_forks(t_data *data, int i) {
  char str[40];

  pthread_mutex_lock(g_mutex_state);
  if (g_time_last_meal[i] != data->begin_time || i % 2 == 0) {
	g_state[i] = HUNGRY;
	test(data, i);
  }
  pthread_mutex_unlock(g_mutex_state);
  pthread_mutex_lock(g_forks[i]);
  pthread_mutex_lock(g_mutex_write);
  ft_create_str(str, data, i + 1, TAKE_FORK);
  write(1, str, ft_strlen(str));
  write(1, str, ft_strlen(str));
  pthread_mutex_unlock(g_mutex_write);
}

void put_forks(t_data *data, int i) {
  pthread_mutex_lock(g_mutex_state);
  g_state[i] = THINKING_OR_SLEEPING;
  test(data, (i + data->number_of_philosos - 1) % data->number_of_philosos);
  test(data, (i + 1) % data->number_of_philosos);
  pthread_mutex_unlock(g_mutex_state);
}
