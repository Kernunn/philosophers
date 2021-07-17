#include "struct.h"
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "create_str_from_time.h"

extern sem_t	*g_sem_for_get;
extern sem_t	*g_sem_forks;
extern sem_t	*g_sem_for_write;

void	take_forks(t_data *data, int i)
{
	char	str[33];

	sem_wait(g_sem_for_get);
	sem_wait(g_sem_forks);
	ft_create_str(str, data, i + 1, TAKE_FORK);
	sem_wait(g_sem_for_write);
	write(1, str, ft_strlen(str));
	sem_post(g_sem_for_write);
	sem_wait(g_sem_forks);
	ft_create_str(str, data, i + 1, TAKE_FORK);
	sem_wait(g_sem_for_write);
	write(1, str, ft_strlen(str));
	sem_post(g_sem_for_write);
	sem_post(g_sem_for_get);
}

void	put_forks(void)
{
	sem_post(g_sem_forks);
	sem_post(g_sem_forks);
}
