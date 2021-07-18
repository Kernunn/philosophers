#include "struct.h"
#include "libft.h"

pthread_mutex_t *restrict
g_mutex_state;
pthread_mutex_t **restrict
g_forks;
pthread_mutex_t **restrict
g_death;
pthread_mutex_t *restrict
g_mutex_write;
t_state *g_state;
long long int *g_time_last_meal;

int allocate_memory(t_data *data) {
  int i;

  i = data->number_of_philosos;
  if (!(data->tid = ft_calloc(i + 1, sizeof(pthread_t))))
	return (-1);
  if (!(g_state = ft_calloc(i, sizeof(t_state))))
	return (-1);
  if (!(g_mutex_write = ft_calloc(1, sizeof(pthread_mutex_t))))
	return (-1);
  if (!(g_mutex_state = ft_calloc(1, sizeof(pthread_mutex_t))))
	return (-1);
  if (!(g_forks = ft_calloc(i, sizeof(pthread_mutex_t * ))))
	return (-1);
  if (!(g_death = ft_calloc(i, sizeof(pthread_mutex_t * ))))
	return (-1);
  i = 0;
  while (i < data->number_of_philosos) {
	if (!(g_death[i] = ft_calloc(1, sizeof(pthread_mutex_t))))
	  return (-1);
	if (!(g_forks[i] = ft_calloc(1, sizeof(pthread_mutex_t))))
	  return (-1);
	i++;
  }
  return (0);
}

int init_mutex(t_data *data) {
  int i;

  if (pthread_mutex_init(g_mutex_write, NULL) != 0)
	return (-1);
  if (pthread_mutex_init(g_mutex_state, NULL) != 0)
	return (-1);
  i = 0;
  while (i < data->number_of_philosos) {
	if (pthread_mutex_init(g_forks[i], NULL) != 0)
	  return (-1);
	if (i % 2 == 0) {
	  if (pthread_mutex_lock(g_forks[i]) != 0)
		return (-1);
	} else
	  g_state[i] = EATING;
	if (pthread_mutex_init(g_death[i], NULL) != 0)
	  return (-1);
	i++;
  }
  return (0);
}

int init_value(t_data *data, char **argv) {
  data->tid = NULL;
  if ((data->number_of_philosos = ft_atoi(*argv++)) < 2)
	return (-1);
  if ((data->time_to_die = ft_atoi(*argv++)) < 0)
	return (-1);
  if ((data->time_to_eat = ft_atoi(*argv++)) < 0)
	return (-1);
  if ((data->time_to_sleep = ft_atoi(*argv++)) < 0)
	return (-1);
  if (*argv) {
	if ((data->number_of_times_each_philo_must_eat = ft_atoi(*argv)) < 1)
	  return (-1);
  } else
	data->number_of_times_each_philo_must_eat = -1;
  data->all_count_meal = 0;
  return (0);
}
