/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meltremb <meltremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 15:09:24 by meltremb          #+#    #+#             */
/*   Updated: 2023/05/31 09:04:37 by meltremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>

typedef struct s_philosopher
{
	pthread_t	thread_id;
	bool		is_eating;
	bool		is_sleeping;
	bool		is_thinking;
	bool		is_dead;
	int			times_eaten;
	int			time_last_ate;
}				t_philosopher;

typedef struct s_data
{
	t_philosopher	*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	end;
	struct timeval	*start_time;
	bool			is_everyone_alive;
	int				nb_philosophers;
	int				time_die;
	int				time_sleep;
	int				time_eat;
	int				max_times_eat;
}						t_data;

void	init(int argc, char **argv);
int		check_args(int argc, char **argv);
void	*ft_calloc(size_t count, size_t size);
int		ft_atoi(const char *str);
int		ft_str_isdigit(char *str);
char	**ft_split(char const *s, char c);
int		get_timestamp(void);
void	take_forks(int i);
void	eat(int i);
void	sleepies(int i);
void	think(int i);
void	die(int i);
t_data	*get_data(void);
void	*print(int type, int position);
int		exit_thread(char *message);
void	smart_sleepies(int time, int position);
int		am_i_dead(int position);
int		is_anyone_dead(void);
void	free_all(void);

#endif