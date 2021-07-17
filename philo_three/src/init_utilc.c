#include "struct.h"
#include "libft.h"
#include <semaphore.h>
#include <fcntl.h>
#include <string.h>

int			allocate_memory(t_data *data)
{
	if (!(data->pid = ft_calloc(data->number_of_philosos + 2,
								sizeof(pthread_t))))
		return (-1);
	if (!(data->sem_death = ft_calloc(data->number_of_philosos,
					sizeof(sem_t*))))
		return (-1);
	return (0);
}

static void	create_name(char *tmp, int i)
{
	memset(tmp, '\0', 13);
	ft_memcpy(tmp, "sem_death", 9);
	ft_itoa(tmp + 9, i);
}

static int	open_while(sem_t **sem, int count)
{
	int		i;
	char	tmp[13];

	i = 0;
	while (i < count)
	{
		create_name(tmp, i);
		sem_unlink(tmp);
		if ((sem[i++] = sem_open(tmp, O_CREAT | O_RDWR,
						0644, 1)) == SEM_FAILED)
			return (-1);
	}
	return (0);
}

int			open_sem(t_data *data)
{
	sem_unlink("sem_for_write");
	if ((data->sem_for_write = sem_open("sem_for_write", O_CREAT | O_RDWR,
					0644, 1)) == SEM_FAILED)
		return (-1);
	sem_unlink("sem_for_get");
	if ((data->sem_for_get = sem_open("sem_for_get", O_CREAT | O_RDWR,
					0644, 1)) == SEM_FAILED)
		return (-1);
	sem_unlink("sem_forks");
	if ((data->sem_forks = sem_open("sem_forks", O_CREAT | O_RDWR,
					0644, data->number_of_philosos)) == SEM_FAILED)
		return (-1);
	sem_unlink("sem_for_stop");
	if ((data->sem_for_stop = sem_open("sem_for_stop", O_CREAT | O_RDWR,
									0644, 0)) == SEM_FAILED)
		return (-1);
	sem_unlink("sem_for_died");
	if ((data->sem_for_died = sem_open("sem_for_died", O_CREAT | O_RDWR,
					0644, 0)) == SEM_FAILED)
		return (-1);
	if (open_while(data->sem_death, data->number_of_philosos) == -1)
		return (-1);
	return (0);
}

int			init_value(t_data *data, char **argv)
{
	data->sem_for_stop = NULL;
	data->pid = NULL;
	data->sem_for_get = NULL;
	data->sem_for_died = NULL;
	data->sem_forks = NULL;
	data->sem_for_write = NULL;
	data->sem_death = NULL;
	if ((data->number_of_philosos = ft_atoi(*argv++)) < 2)
		return (-1);
	if ((data->time_to_die = ft_atoi(*argv++)) < 1)
		return (-1);
	if ((data->time_to_eat = ft_atoi(*argv++)) < 1)
		return (-1);
	if ((data->time_to_sleep = ft_atoi(*argv++)) < 1)
		return (-1);
	if (*argv)
	{
		if ((data->number_of_times_each_philosopher_must_eat = ft_atoi(*argv))
			< 1)
			return (-1);
	}
	else
		data->number_of_times_each_philosopher_must_eat = -1;
	return (0);
}
