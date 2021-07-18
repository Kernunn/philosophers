#include <semaphore.h>
#include "philosophy_of_action.h"
#include <sys/time.h>
#include <unistd.h>
#include "libft.h"
#include "struct.h"
#include "create_str_from_time.h"
#include <stdlib.h>

extern sem_t **g_sem_death;
extern sem_t *g_sem_for_write;
extern long long int *g_time_last_meal;

void *philosophers(void *arg) {
  int i;
  int count_meal;
  t_data *data;

  count_meal = 0;
  i = ((t_args *) arg)->number_of_the_philosopher;
  data = ((t_args *) arg)->data;
  while (1) {
	take_forks(data, i);
	eating(data, i);
	put_forks();
	count_meal++;
	if (count_meal == data->number_of_times_each_philo_must_eat)
	  data->all_count_meal += 1;
	sleeping_and_thinking(data, i);
  }
  return (NULL);
}

static void *print(t_data *data, int status, int i) {
  char str[33];

  sem_wait(g_sem_for_write);
  if (status == 1)
	write(1, "Simulation was stopped\n", 23);
  else {
	sem_wait(g_sem_death[i]);
	ft_create_str(str, data, i + 1, IS_DIED);
	write(1, str, ft_strlen(str));
  }
  return (NULL);
}

void *check_state(void *arg) {
  struct timeval time;
  long long int time_in_ms;
  int i;
  t_data *data;

  data = arg;
  while (1) {
	if (data->number_of_times_each_philo_must_eat != -1 &&
		data->all_count_meal == data->number_of_philosos)
	  return (print(data, 1, 0));
	i = 0;
	while (i < data->number_of_philosos) {
	  gettimeofday(&time, NULL);
	  time_in_ms = time.tv_sec * 1000000 + time.tv_usec;
	  if (time_in_ms - g_time_last_meal[i] >= data->time_to_die * 1000)
		return (print(data, 2, i));
	  i++;
	}
  }
}
