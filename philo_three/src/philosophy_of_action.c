#include "struct.h"
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "create_str_from_time.h"

void take_forks(t_data *data, int i) {
  char str[33];

  sem_wait(data->sem_for_get);
  sem_wait(data->sem_forks);
  ft_create_str(str, data, i + 1, TAKE_FORK);
  sem_wait(data->sem_for_write);
  write(1, str, ft_strlen(str));
  sem_post(data->sem_for_write);
  sem_wait(data->sem_forks);
  ft_create_str(str, data, i + 1, TAKE_FORK);
  sem_wait(data->sem_for_write);
  write(1, str, ft_strlen(str));
  sem_post(data->sem_for_write);
  sem_post(data->sem_for_get);
}

void put_forks(t_data *data) {
  sem_post(data->sem_forks);
  sem_post(data->sem_forks);
}
