#include "struct.h"
#include <sys/time.h>
#include "libft.h"
#include <string.h>
#include "create_str_from_time.h"

void	ft_create_str(char *str, t_data *data, int i, int option)
{
	struct timeval	time;
	long long int	time_in_ms;
	int				length;

	gettimeofday(&time, NULL);
	time_in_ms = (time.tv_sec * 1000000 + time.tv_usec);
	memset(str, '\0', 40);
	ft_itoa(str, (time_in_ms - data->begin_time) / 1000);
	length = ft_strlen(str);
	str[length++] = ' ';
	ft_itoa(str + length, i);
	length = ft_strlen(str);
	if (option == TAKE_FORK)
		ft_memcpy(str + length, " has taken a fork\n", 18);
	else if (option == IS_EATING)
		ft_memcpy(str + length, " is eating\n", 11);
	else if (option == IS_SLEEPING)
		ft_memcpy(str + length, " is sleeping\n", 13);
	else if (option == IS_THINKING)
		ft_memcpy(str + length, " is thinking\n", 13);
	else
		ft_memcpy(str + length, " is died\n", 9);
}
