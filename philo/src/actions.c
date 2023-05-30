/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meltremb <meltremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:36:54 by meltremb          #+#    #+#             */
/*   Updated: 2023/05/30 13:44:45 by meltremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/philosophers.h"

void	eat(int i)
{
	t_data	*d;

	d = get_data();
	pthread_mutex_lock(&d->forks[i]);
	print(1, i);
	if (i == 1)
		pthread_mutex_lock(&d->forks[d->nb_philosophers]);
	else
		pthread_mutex_lock(&d->forks[i - 1]);
	print(1, i);
	if (d->philo[i].is_thinking == true)
		d->philo[i].is_thinking = false;
	d->philo[i].is_eating = true;
	print(2, i);
	d->philo[i].time_last_ate = get_timestamp();
	smart_sleepies(d->time_eat, i);
	d->philo[i].times_eaten += 1;
	d->philo[i].is_eating = false;
	pthread_mutex_unlock(&d->forks[i]);
	if (i == 1)
		pthread_mutex_unlock(&d->forks[d->nb_philosophers]);
	else
		pthread_mutex_unlock(&d->forks[i - 1]);
}

void	sleepies(int i)
{
	t_data	*d;

	d = get_data();
	if (d->is_everyone_alive == true)
	{
		d->philo[i].is_sleeping = true;
		print(3, i);
		smart_sleepies(d->time_sleep, i);
		d->philo[i].is_sleeping = false;
	}
}

void	think(int i)
{
	t_data	*d;

	d = get_data();
	if (d->is_everyone_alive == true)
	{
		if (d->philo[i].is_dead == false)
		{
			d->philo[i].is_thinking = true;
			print(4, i);
		}
	}
}

void	die(int i)
{
	t_data	*d;

	d = get_data();
	d->philo[i].is_dead = true;
	print(5, i);
	pthread_mutex_lock(&d->end);
	d->is_everyone_alive = false;
	pthread_mutex_unlock(&d->end);
	d->philo[i].is_eating = false;
	d->philo[i].is_sleeping = false;
	d->philo[i].is_thinking = false;
}
