#include "struct.h"
#include "init_utilc.h"
#include "libft.h"
#include <stdlib.h>
#include "ft_free.h"
#include <sys/time.h>

extern long long int *g_time_last_meal;

static int get_time(t_data *data) {
  struct timeval time;
  int i;

  if (gettimeofday(&time, NULL) != 0)
	return (-1);
  data->begin_time = time.tv_sec * 1000000 + time.tv_usec;
  i = 0;
  if (!(g_time_last_meal = malloc(sizeof(long long int) *
	  data->number_of_philosos)))
	return (-1);
  while (i < data->number_of_philosos) {
	g_time_last_meal[i] = data->begin_time;
	i++;
  }
  return (0);
}

static t_data *get_value(char **argv) {
  t_data *data;

  if (!(data = malloc(sizeof(t_data))))
	return (NULL);
  if (init_value(data, argv) == -1) {
	ft_free_data(data);
	return (NULL);
  }
  if (allocate_memory(data) == -1) {
	ft_free_data(data);
	return (NULL);
  }
  if (init_mutex(data) == -1) {
	ft_free_data(data);
	return (NULL);
  }
  return (data);
}

t_data *init_data(char **argv) {
  t_data *data;

  if ((data = get_value(argv)) == NULL)
	return (NULL);
  if (get_time(data) == -1) {
	ft_free_data(data);
	return (NULL);
  }
  return (data);
}
