/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meltremb <meltremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 13:16:55 by meltremb          #+#    #+#             */
/*   Updated: 2023/05/31 09:06:00 by meltremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/philosophers.h"

int	am_i_dead(int i)
{
	t_data	*d;

	d = get_data();
	if (get_timestamp() - d->philo[i].time_last_ate >= d->time_die)
	{
		pthread_mutex_lock(&d->print);
		pthread_mutex_unlock(&d->print);
		die(i);
		return (1);
	}
	return (0);
}

int	is_anyone_dead(void)
{
	int		i;
	t_data	*d;

	d = get_data();
	i = 0;
	while (++i <= d->nb_philosophers)
	{
		if (am_i_dead(i) == 1)
			return (1);
	}
	return (0);
}

void	smart_sleepies(int time, int position)
{
	t_data	*d;
	int		initial_time;

	d = get_data();
	initial_time = get_timestamp();
	while (get_timestamp() - initial_time < time)
	{
		if (am_i_dead(position) == 1 || is_anyone_dead() == 1)
			break ;
		usleep(1000);
	}
}
