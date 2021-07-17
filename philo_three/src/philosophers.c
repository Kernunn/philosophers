#include <semaphore.h>
#include "philosophy_of_action.h"
#include <sys/time.h>
#include <unistd.h>
#include "libft.h"
#include "struct.h"
#include "create_str_from_time.h"
#include <stdlib.h>

void		*philosophers(void *arg)
{
	int		i;
	int		count_meal;
	t_data	*data;

	count_meal = 0;
	i = ((t_args*)arg)->number_of_the_philosopher;
	data = ((t_args*)arg)->data;
	while (1)
	{
		take_forks(data, i);
		eating(data, i);
		put_forks(data);
		count_meal++;
		if (data->number_of_times_each_philosopher_must_eat &&
		count_meal == data->number_of_times_each_philosopher_must_eat)
			sem_post(data->sem_for_stop);
		sleeping_and_thinking(data, i);
	}
}

static int	print(t_data *data, int i)
{
	char	str[33];

	sem_wait(data->sem_for_write);
	sem_wait(data->sem_death[i]);
	ft_create_str(str, data, i + 1, IS_DIED);
	write(1, str, ft_strlen(str));
	sem_post(data->sem_for_died);
	return (0);
}

void		check_number_of_well_fed_philosophers(t_data *data)
{
	int i;

	i = 0;
	while (i < data->number_of_philosos)
	{
		sem_wait(data->sem_for_stop);
		i++;
	}
	sem_wait(data->sem_for_write);
	write(1, "Simulation was stopped\n", 23);
	exit(0);
}

void		check_philosopher_death(t_data *data)
{
	sem_wait(data->sem_for_died);
	exit(0);
}

void		*check_state(void *arg)
{
	struct timeval	time;
	long long int	time_in_ms;
	t_data			*data;
	int				i;

	i = ((t_args*)arg)->number_of_the_philosopher;
	data = ((t_args*)arg)->data;
	while (1)
	{
		gettimeofday(&time, NULL);
		time_in_ms = time.tv_sec * 1000000 + time.tv_usec;
		if (time_in_ms - data->time_last_meal >=
				data->time_to_die * 1000)
			exit(print(data, i));
		usleep(2000);
	}
}
