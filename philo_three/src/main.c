#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "init.h"
#include "create_args.h"
#include "philosophers.h"
#include "ft_free.h"

int		create_check_fork(t_data *data, int i)
{
	if ((data->pid[i] = fork()) == -1)
		return (-1);
	else if (data->pid[i] == 0)
		check_number_of_well_fed_philosophers(data);
	i++;
	if ((data->pid[i] = fork()) == -1)
		return (-1);
	else if (data->pid[i] == 0)
		check_philosopher_death(data);
	return (0);
}

int		create_fork(t_args **args, t_data *data)
{
	int			i;
	pthread_t	tid;

	i = 0;
	while (i < data->number_of_philosos)
	{
		if ((data->pid[i] = fork()) == -1)
			return (-1);
		else if (data->pid[i] == 0)
		{
			if (pthread_create(&tid, NULL, philosophers, args[i]) != 0)
				exit(ft_free_data(data) && ft_free_args(args));
			check_state(args[i]);
		}
		i++;
	}
	if (create_check_fork(data, i) == -1)
		return (-1);
	return (0);
}

void	*wait_proc(void *arg)
{
	int		i;
	int		j;
	t_data	*data;

	i = ((t_args*)arg)->number_of_the_philosopher;
	data = ((t_args*)arg)->data;
	pthread_detach(data->tid1);
	pthread_detach(data->tid2);
	waitpid(data->pid[i], NULL, 0);
	j = 0;
	while (j < data->number_of_philosos + 2)
		kill(data->pid[j++], SIGKILL);
	return (NULL);
}

void	wait_all_processes(t_args **args, t_data *data)
{
	int	i;

	if (pthread_create(&data->tid1, NULL, wait_proc,
				args[data->number_of_philosos]) != 0)
		exit(10);
	if (pthread_create(&data->tid2, NULL, wait_proc,
				args[data->number_of_philosos + 1]) != 0)
		exit(10);
	i = 0;
	while (i < data->number_of_philosos + 2)
		waitpid(data->pid[i++], NULL, 0);
}

int		main(int argc, char *argv[])
{
	t_data	*data;
	t_args	**args;

	if (argc < 5 || argc > 6)
		return (1);
	if ((data = init_data(++argv)) == NULL)
		return (1);
	if ((args = create_args(data)) == NULL)
		return (ft_free_data(data));
	if (create_fork(args, data) == -1)
		return (ft_free_data(data) && ft_free_args(args));
	wait_all_processes(args, data);
	ft_free_data(data);
	ft_free_args(args);
	return (0);
}
