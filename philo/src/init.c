/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meltremb <meltremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:34:09 by meltremb          #+#    #+#             */
/*   Updated: 2023/05/11 14:47:32 by meltremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/philosophers.h"

void	init(int argc, char **argv, t_data *d)
{
	int	i;

	d->nb_philosophers = ft_atoi(argv[1]);
	d->philosophers = ft_calloc((d->nb_philosophers + 2), sizeof(t_philosopher));
	d->forks = ft_calloc((d->nb_philosophers + 1), sizeof(pthread_mutex_t));
	d->start_time = ft_calloc(1, sizeof(struct timeval));
	d->time_die = ft_atoi(argv[2]);
	d->time_eat = ft_atoi(argv[3]);
	d->time_sleep =	ft_atoi(argv[4]);
	d->is_everyone_alive = true;
	pthread_mutex_init(&d->end, NULL);
	if (argc == 6)
		d->max_times_eat = ft_atoi(argv[5]);
	i = 0;
	while (i++ <= d->nb_philosophers)
		pthread_mutex_init(&d->forks[i], NULL);
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