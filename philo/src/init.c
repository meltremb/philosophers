/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meltremb <meltremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:34:09 by meltremb          #+#    #+#             */
/*   Updated: 2023/05/30 13:44:01 by meltremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/philosophers.h"

void	init(int argc, char **argv)
{
	int		i;
	t_data	*d;

	d = get_data();
	d->nb_philosophers = ft_atoi(argv[1]);
	d->philo = ft_calloc((d->nb_philosophers + 2),
			sizeof(t_philosopher));
	d->forks = ft_calloc((d->nb_philosophers + 1), sizeof(pthread_mutex_t));
	d->start_time = ft_calloc(1, sizeof(struct timeval));
	d->time_die = ft_atoi(argv[2]);
	d->time_eat = ft_atoi(argv[3]);
	d->time_sleep = ft_atoi(argv[4]);
	d->is_everyone_alive = true;
	pthread_mutex_init(&d->end, NULL);
	if (argc == 6)
		d->max_times_eat = ft_atoi(argv[5]);
	i = 0;
	while (++i <= d->nb_philosophers)
	{
		if (argc == 6)
			d->philo[i].times_eaten = 0;
		pthread_mutex_init(&d->forks[i], NULL);
	}
}

int	check_args(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (0);
	i = 0;
	while (argv[++i])
	{
		if (!ft_str_isdigit(*argv))
			return (0);
		else if (ft_str_isdigit(*argv))
			if (ft_atoi(*argv))
				return (0);
	}
	return (1);
}
