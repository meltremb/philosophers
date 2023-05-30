/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meltremb <meltremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 15:10:07 by meltremb          #+#    #+#             */
/*   Updated: 2023/05/30 16:02:57 by meltremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/philosophers.h"

void	*do_stuff_one(void *arg)
{
	int		position;
	t_data	*d;

	d = get_data();
	position = *(int *)arg;
	pthread_mutex_lock(&d->print);
	pthread_mutex_unlock(&d->print);
	pthread_mutex_lock(&d->forks[position]);
	print(1, position);
	while (am_i_dead(position) == 0)
	{
		if (d->is_everyone_alive == false)
			break ;
		am_i_dead(position);
	}
	return (NULL);
}

void	*do_stuff(void *arg)
{
	int		position;
	t_data	*d;

	d = get_data();
	position = *(int *)arg;
	pthread_mutex_lock(&d->print);
	pthread_mutex_unlock(&d->print);
	if (position % 2 == 0)
		usleep(100);
	while (am_i_dead(position) != 1)
	{
		if (d->is_everyone_alive == false)
			break ;
		eat(position);
		if (d->philo[position].times_eaten == d->max_times_eat)
			break ;
		sleepies(position);
		while (am_i_dead(position) != 1)
			think(position);
	}
	return (NULL);
}

void	philosophers(void)
{
	int		i;
	t_data	*d;

	d = get_data();
	if (pthread_mutex_init(&d->print, NULL))
		exit_thread("Error creating mutex");
	gettimeofday(d->start_time, NULL);
	pthread_mutex_lock(&d->print);
	if (d->nb_philosophers == 1)
	{
		i = 1;
		if (pthread_create(&d->philo[i].thread_id, NULL, &do_stuff_one, &i))
			exit_thread("Error creating thread");
	}
	else
	{
		i = 0;
		while (++i <= d->nb_philosophers)
		{
			if (pthread_create(&d->philo[i].thread_id, NULL, &do_stuff, &i))
				exit_thread("Error creating thread");
			usleep(100);
		}
	}
	pthread_mutex_unlock(&d->print);
}

int	main(int argc, char **argv)
{
	t_data	*d;
	int		i;

	if (argc == 5 || argc == 6)
	{
		if (!check_args(argc, argv))
			return (0);
		init(argc, argv);
		philosophers();
		i = 0;
		d = get_data();
		while (++i <= d->nb_philosophers)
			if (d->philo[i].thread_id)
				pthread_join(d->philo[i].thread_id, NULL);
		free_all();
	}
	return (0);
}
