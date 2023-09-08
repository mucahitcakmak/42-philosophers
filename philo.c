#include "philo.h"

int	get_ms(unsigned long start_usec)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec - start_usec));
}

void	*thread(void	*numara)
{
	return (NULL);
}

t_philo_info	*arguman_init(t_philo_info *pi, char **argv)
{
	long	i;

	pi->size_of_philo = ft_atoi(argv[1]);
	pi->die_time = ft_atoi(argv[2]);
	pi->eat_time = ft_atoi(argv[3]);
	pi->sleep_time = ft_atoi(argv[4]);
	pi->think_time = (ft_atoi(argv[2]) - ft_atoi(argv[4]));
	if (argv[5])
		pi->eat_limit = ft_atoi(argv[5]);
	pi->philos = malloc(sizeof(t_philo) * pi->size_of_philo);
	pi->forks = malloc(sizeof(pthread_mutex_t) * pi->size_of_philo);
	i = -1;
	while (++i < pi->size_of_philo)
	{
		pthread_mutex_init(&pi->forks[i], NULL);
		pi->philos->last_eat_time = pi->start_ms;
		if (pthread_create(&pi->philos[i].thread, NULL, &thread, (void *)i) != 0)
			printf("Hata: Thread oluşturulamadı.\n");
		usleep(1);
	}
	return (pi);
}

int main(int ac, char **argv)
{
	t_philo_info	*pi;
	struct timeval tv;
	printf("-----------------\n");

	pi = malloc(sizeof(t_philo_info));
	gettimeofday(&tv, NULL);
	pi->start_ms = tv.tv_sec;

	if (ac != 5 && ac != 6)
		return (1);
	arguman_init(pi, argv);
	
	philo_life_cycle(pi);

	printf("\n-----------------\n");

    return (0);
}

/*
Filozof sayısı tek olduğunda hatalı çalışıyor.
Filozof sayısı çift girildiğinde;
- Kaşığı ilk alan filozoflar düşünme ve uyuma işlemini bitirdikten sonra kaşığı bırakıyor.
*/