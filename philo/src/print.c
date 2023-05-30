/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meltremb <meltremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:36:23 by meltremb          #+#    #+#             */
/*   Updated: 2023/05/30 14:48:36 by meltremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/philosophers.h"

void	*print(int type, int position)
{
	t_data	*d;

	d = get_data();
	pthread_mutex_lock(&d->print);
	if (d->is_everyone_alive == true)
	{
		if (type == 1)
			printf("%d %d has taken a fork\n", get_timestamp(), position);
		else if (type == 2)
			printf("%d %d is eating\n", get_timestamp(), position);
		else if (type == 3)
			printf("%d %d is sleeping\n", get_timestamp(), position);
		else if (type == 4)
			printf("%d %d is thinking\n", get_timestamp(), position);
		else if (type == 5)
			printf("%d %d is dead\n", get_timestamp(), position);
	}
	pthread_mutex_unlock(&d->print);
	return (NULL);
}

void	free_all(void)
{
	t_data	*d;
	int		i;

	d = get_data();
	i = -1;
	while (++i <= d->nb_philosophers)
		pthread_mutex_destroy(&d->forks[i]);
	pthread_mutex_destroy(&d->print);
	pthread_mutex_destroy(&d->end);
	free(d->forks);
	free(d->philo);
	free(d->start_time);
	free(d);
}

int	exit_thread(char *message)
{
	printf("%s\n", message);
	free_all();
	return (1);
}
