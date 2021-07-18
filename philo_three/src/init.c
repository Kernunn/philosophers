#include "struct.h"
#include "init_utilc.h"
#include "libft.h"
#include <stdlib.h>
#include "ft_free.h"
#include <sys/time.h>

static int get_time(t_data *data) {
  struct timeval time;

  if (gettimeofday(&time, NULL) != 0)
	return (-1);
  data->begin_time = time.tv_sec * 1000000 + time.tv_usec;
  data->time_last_meal = data->begin_time;
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
  if (open_sem(data) == -1) {
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
