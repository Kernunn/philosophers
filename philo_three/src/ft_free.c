#include <stdlib.h>
#include "struct.h"
#include <semaphore.h>
#include "libft.h"
#include <string.h>

void ft_sem_destroy(sem_t *sem, char const *name) {
  sem_close(sem);
  sem_unlink(name);
}

static void create_name(char *tmp, int i) {
  memset(tmp, '\0', 13);
  ft_memcpy(tmp, "sem_death", 9);
  ft_itoa(tmp + 9, i);
}

static void free_while(sem_t **sem, int count) {
  int i;
  char tmp[13];

  i = 0;
  if (!sem)
	return;
  while (i < count) {
	create_name(tmp, i);
	sem_close(sem[i]);
	sem_unlink(tmp);
	i++;
  }
}

int ft_free_data(t_data *data) {
  if (data->sem_death)
	free_while(data->sem_death, data->number_of_philosos);
  if (data->sem_for_get)
	ft_sem_destroy(data->sem_for_get, "sem_for_get");
  if (data->sem_for_write)
	ft_sem_destroy(data->sem_for_write, "sem_for_write");
  if (data->sem_forks)
	ft_sem_destroy(data->sem_forks, "sem_forks");
  if (data->sem_for_stop)
	ft_sem_destroy(data->sem_for_stop, "sem_for_stop");
  if (data->sem_for_died)
	ft_sem_destroy(data->sem_for_died, "sem_for_died");
  free(data->pid);
  free(data->sem_death);
  free(data);
  return (1);
}

int ft_free_args(t_args **args) {
  int i;

  i = 0;
  if (args) {
	while (args[i])
	  free(args[i++]);
  }
  free(args);
  return (1);
}
