/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mryan <mryan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 18:40:34 by mryan             #+#    #+#             */
/*   Updated: 2021/07/28 19:19:48 by mryan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time_int(t_table *table)
{
	struct timeval	current_time;
	long			n;

	gettimeofday(&current_time, NULL);
	current_time.tv_sec = current_time.tv_sec - table->start_time.tv_sec;
	current_time.tv_usec = current_time.tv_usec - table->start_time.tv_usec;
	n = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (n);
}

long	get_time(void)
{
	struct timeval	current_time;
	long			n;

	gettimeofday(&current_time, NULL);
	n = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (n);
}

int	my_sleep(int sleep)
{
	long int	time;

	time = get_time();
	while (get_time() - time < sleep)
		usleep(50);
	return (1);
}

void	forks_unlock(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->ph_num)
	{
		pthread_mutex_unlock(&table->forks[i]);
		i++;
	}
}

int	count_meals(t_table *table)
{
	int				i;
	t_philo			*philo;

	i = 0;
	while (i < table->ph_num)
	{
		philo = &table->philos[i];
		if (table->philos[i].num_meals != table->num_eat)
			return (1);
		i++;
	}
	return (0);
}
