/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meltremb <meltremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 12:38:14 by meltremb          #+#    #+#             */
/*   Updated: 2023/05/10 12:25:39 by meltremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/philosophers.h"

int	get_timestamp(void)
{
	t_data			*d;
	int				timestamp;
	struct timeval	*current_time;

	d = get_data();
	current_time = ft_calloc(1, sizeof(struct timeval));
	gettimeofday(current_time, NULL);
	timestamp = (((current_time->tv_sec - d->start_time->tv_sec) * 1000) + ((current_time->tv_usec - d->start_time->tv_usec) / 1000));
	free(current_time);
	return (timestamp);
}