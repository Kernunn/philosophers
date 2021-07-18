#include <pthread.h>
#include <unistd.h>
#include "init.h"
#include "create_args.h"
#include "philosophers.h"
#include "ft_free.h"

extern pthread_mutex_t **restrict
g_death;

int create_thread(t_args **args, t_data *data) {
  int i;

  i = 0;
  while (i < data->number_of_philosos) {
	pthread_mutex_unlock(g_death[i]);
	if (pthread_create(&data->tid[i], NULL, philosophers, args[i]) != 0)
	  return (-1);
	i++;
  }
  return (0);
}

int main(int argc, char *argv[]) {
  t_data *data;
  t_args **args;

  if (argc < 5 || argc > 6)
	return (1);
  if ((data = init_data(++argv)) == NULL)
	return (1);
  if ((args = create_args(data)) == NULL)
	return (ft_free_data(data));
  if (create_thread(args, data) == -1)
	return (ft_free_data(data) && ft_free_args(args));
  if (pthread_create(&data->tid[data->number_of_philosos],
					 NULL, check_state, data) != 0)
	return (ft_free_data(data) && ft_free_args(args));
  pthread_join(data->tid[data->number_of_philosos], NULL);
  ft_free_data(data);
  ft_free_args(args);
  return (0);
}
