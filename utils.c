#include "philo.h"

unsigned long	get_ms(t_philo_info *pi)
{
	gettimeofday(&pi->tv, NULL);
	return ((pi->tv.tv_usec / 1000 + pi->tv.tv_sec * 1000) - pi->start_ms);
}

void	ms_sleep(t_philo *p, int time)
{
	unsigned long	dest_time;

	dest_time = get_ms(p->pi) + time;
	while (get_ms(p->pi) < dest_time)
		usleep(100);
}

void	destroy_mutex(t_philo_info *pi)
{
	int	i;

	i = -1;
	while (++i < pi->size_of_philo)
		pthread_mutex_destroy(&pi->forks[i]);
}

int	ft_atoi(char *str)
{
	int	i;
	int result;

	i = 0;
	result = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - '0');
		if (result > 2147483647)
			return (-1);
		i++;
	}
	return (result);
}

int	check_arguman(char **argv)
{
	int	i;

	i = -1;
	while (argv[++i])
		if (ft_atoi(argv[i]) == -1)
			return (-1);
	return (0);
}