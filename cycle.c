/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mryan <mryan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 19:33:22 by mryan             #+#    #+#             */
/*   Updated: 2021/08/02 16:47:53 by mryan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	give_forks(t_philo *philo, t_table *table)
{
	if ((philo->index + 1) % 2)
	{
		pthread_mutex_lock(&table->forks[philo->right_fork]);
		pthread_mutex_lock(&table->forks[philo->left_fork]);
		message(table, philo->name, "right fork");
		message(table, philo->name, "left fork");
	}
	else
	{
		pthread_mutex_lock(&table->forks[philo->left_fork]);
		pthread_mutex_lock(&table->forks[philo->right_fork]);
		message(table, philo->name, "left fork");
		message(table, philo->name, "right fork");
	}
}

int	eat(t_table *table, t_philo *philo)
{
	message(table, philo->name, "eat");
	philo->limit = get_time_int(table) + table->time_to_die;
	my_sleep(table->time_to_eat);
	if (table->num_eat != 0)
		philo->num_meals += 1;
	if (table->num_eat != 0)
	{
		if (count_meals(table) == 0)
		{
			message(table, philo->name, "dinner is done");
			table->allowed = 0;
			forks_unlock(table);
			return (1);
		}
	}
	return (0);
}

int	sleep_threads(t_table *table, t_philo *philo)
{
	message(table, philo->name, "sleep");
	my_sleep(table->time_to_sleep);
	return (0);
}

void	*cycle(void *arguments)
{
	t_philo			*philo;
	t_philo_struct	*arg;
	t_table			*table;

	arg = (t_philo_struct *)arguments;
	table = arg->table;
	while (table->allowed)
	{
		philo = arg->philosopher;
		give_forks(philo, table);
		if (eat(table, philo) != 0)
			break ;
		pthread_mutex_unlock(&table->forks[philo->left_fork]);
		pthread_mutex_unlock(&table->forks[philo->right_fork]);
		if (sleep_threads(table, philo) != 0)
			break ;
		message(table, philo->name, "think");
	}
	return ((void *)0);
}
