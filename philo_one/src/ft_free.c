#include <stdlib.h>
#include "init.h"
#include <pthread.h>

int		ft_free_data(t_data *data)
{
	free(data->tid);
	free(data);
	return (1);
}

int		ft_free_args(t_args **args)
{
	int i;

	i = 0;
	if (args)
	{
		while (args[i])
			free(args[i++]);
	}
	free(args);
	return (1);
}
