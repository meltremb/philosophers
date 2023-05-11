/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meltremb <meltremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:36:54 by meltremb          #+#    #+#             */
/*   Updated: 2023/05/11 14:52:41 by meltremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/philosophers.h"

void	eat(t_data *d, int i)
{
	if (d->is_everyone_alive == true)
	{
		pthread_mutex_lock(&d->forks[i]);
		print(1, i);
		if (i == 1)
			pthread_mutex_lock(&d->forks[d->nb_philosophers]);
		else
			pthread_mutex_lock(&d->forks[i - 1]);
		print(1, i);
		if (d->philosophers[i].is_thinking == true)
			d->philosophers[i].is_thinking = false;
		d->philosophers[i].is_eating = true;
		print(2, i);
		d->philosophers[i].time_last_ate = get_timestamp();
		smart_sleepies(d->time_eat, i);
		d->philosophers[i].is_eating = false;
		pthread_mutex_unlock(&d->forks[i]);
		if (i == 1)
			pthread_mutex_unlock(&d->forks[d->nb_philosophers]);
		else
			pthread_mutex_unlock(&d->forks[i - 1]);
	}
}

void	sleepies(t_data *d, int i)
{
	if (d->is_everyone_alive == true)
	{
		if (d->philosophers[i].is_eating == false
				&& d->philosophers[i].is_dead == false)
		{
			d->philosophers[i].is_sleeping = true;
			print(3, i);
			smart_sleepies(d->time_sleep, i);
			d->philosophers[i].is_sleeping = false;
		}
	}
}

void	think(t_data *d, int i)
{
	if (d->is_everyone_alive == true)
	{
		if (d->philosophers[i].is_dead == false)
		{
			d->philosophers[i].is_thinking = true;
			print(4, i);
		}
	}
}

void	die(t_data *d, int i)
{
	d->philosophers[i].is_dead = true;
	print(5, i);
	pthread_mutex_lock(&d->end);
	d->is_everyone_alive = false;
	pthread_mutex_unlock(&d->end);
	d->philosophers[i].is_eating = false;
	d->philosophers[i].is_sleeping = false;
	d->philosophers[i].is_thinking = false;
}