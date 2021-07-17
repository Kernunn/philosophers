#include <stdlib.h>
#include "struct.h"
#include "libft.h"
#include <string.h>

static void	create_name(char *tmp, int i)
{
	memset(tmp, '\0', 15);
	ft_memcpy(tmp, "g_sem_death", 11);
	ft_itoa(tmp + 11, i);
}

int			ft_free_data(t_data *data)
{
	int		i;
	char	tmp[15];

	i = 0;
	sem_unlink("g_sem_for_write");
	sem_unlink("g_sem_for_get");
	sem_unlink("g_sem_forks");
	while (i < data->number_of_philosos)
	{
		create_name(tmp, i);
		sem_unlink(tmp);
		i++;
	}
	free(data);
	return (1);
}

int			ft_free_args(t_args **args)
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
