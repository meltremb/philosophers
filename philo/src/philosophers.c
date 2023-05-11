/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meltremb <meltremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 15:10:07 by meltremb          #+#    #+#             */
/*   Updated: 2023/05/11 15:06:24 by meltremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/philosophers.h"

void	*do_stuff(void *arg)
{
	int		position;
	t_data	*d;

	d = get_data();
	position = *(int *)arg;
	if (position % 2 == 0)
		usleep(100);
	while (am_i_dead(position) == 0)
	{
		if (d->is_everyone_alive == false)
			break ;
		eat(d, position);
		sleepies(d, position);
		think(d, position);
	}
	return (NULL);
}

void	philosophers(t_data *d)
{
	int	i;

	if (pthread_mutex_init(&d->print, NULL))
		exit_thread("Error creating mutex");
	gettimeofday(d->start_time, NULL);
	i = 0;
	while (++i <= d->nb_philosophers)
	{
		pthread_mutex_lock(&d->print);
		if (pthread_create(&d->philosophers[i].thread_id, NULL, &do_stuff, &i))
			exit_thread("Error creating thread");
		pthread_mutex_unlock(&d->print);
		usleep(1);
	}
}

int	main(int argc, char **argv)
{
	t_data	*d;
	int	i;

	if (argc == 5 || argc == 6)
	{
		if (!check_args(argc, argv))
			return (0);
		d = get_data();
		init(argc, argv, d);
		philosophers(d);
		i = 0;
		while (++i <= d->nb_philosophers)
			pthread_join(d->philosophers[i].thread_id, NULL);
		free_all();
	}
	return (0);
}
