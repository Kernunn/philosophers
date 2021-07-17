#include "struct.h"
#include "libft.h"
#include "stdlib.h"
#include "ft_free.h"

t_args	**create_args(t_data *data)
{
	int		i;
	t_args	**args;

	if (!(args = ft_calloc((data->number_of_philosos + 2), sizeof(t_args*))))
		return (NULL);
	i = 0;
	while (i < data->number_of_philosos + 1)
	{
		if (!(args[i] = malloc(sizeof(t_args))))
		{
			ft_free_args(args);
			return (NULL);
		}
		args[i]->number_of_the_philosopher = i;
		args[i]->data = data;
		i++;
	}
	return (args);
}
