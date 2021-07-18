#include "struct.h"
#include "libft.h"
#include <semaphore.h>
#include <fcntl.h>
#include <string.h>

pthread_t *g_tid;
sem_t *g_sem_for_get;
sem_t *g_sem_forks;
sem_t **g_sem_death;
sem_t *g_sem_for_write;
long long int *g_time_last_meal;

int allocate_memory(t_data *data) {
  if (!(g_tid = ft_calloc(data->number_of_philosos + 1, sizeof(pthread_t))))
	return (-1);
  if (!(g_sem_death = ft_calloc(data->number_of_philosos, sizeof(sem_t * ))))
	return (-1);
  return (0);
}

static void create_name(char *tmp, int i) {
  memset(tmp, '\0', 15);
  ft_memcpy(tmp, "g_sem_death", 11);
  ft_itoa(tmp + 11, i);
}

int open_sem(t_data *data) {
  int i;
  char tmp[15];

  i = 0;
  sem_unlink("g_sem_for_write");
  if ((g_sem_for_write = sem_open("g_sem_for_write", O_CREAT | O_RDWR,
								  0644, 1)) == SEM_FAILED)
	return (-1);
  sem_unlink("g_sem_for_get");
  if ((g_sem_for_get = sem_open("g_sem_for_get", O_CREAT | O_RDWR,
								0644, 1)) == SEM_FAILED)
	return (-1);
  sem_unlink("g_sem_forks");
  if ((g_sem_forks = sem_open("g_sem_forks", O_CREAT | O_RDWR,
							  0644, data->number_of_philosos)) == SEM_FAILED)
	return (-1);
  while (i < data->number_of_philosos) {
	create_name(tmp, i);
	sem_unlink(tmp);
	if ((g_sem_death[i++] = sem_open(tmp, O_CREAT | O_RDWR,
									 0644, 1)) == SEM_FAILED)
	  return (-1);
  }
  return (0);
}

int init_value(t_data *data, char **argv) {
  if ((data->number_of_philosos = ft_atoi(*argv++)) < 2)
	return (-1);
  if ((data->time_to_die = ft_atoi(*argv++)) < 1)
	return (-1);
  if ((data->time_to_eat = ft_atoi(*argv++)) < 1)
	return (-1);
  if ((data->time_to_sleep = ft_atoi(*argv++)) < 1)
	return (-1);
  if (*argv) {
	if ((data->number_of_times_each_philo_must_eat = ft_atoi(*argv)) < 1)
	  return (-1);
  } else
	data->number_of_times_each_philo_must_eat = -1;
  data->all_count_meal = 0;
  return (0);
}
