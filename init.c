/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mryan <mryan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 18:38:27 by mryan             #+#    #+#             */
/*   Updated: 2021/07/28 15:11:19 by mryan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_philosopher(t_philo *philosopher, char *name,
						unsigned left_fork, unsigned right_fork)
{
	philosopher->name = name;
	philosopher->left_fork = left_fork;
	philosopher->right_fork = right_fork;
	philosopher->limit = 0;
	philosopher->last_meal = 0;
	philosopher->num_meals = 0;
}

void	call_philosophers(t_philo *philosophers, t_table *table)
{
	int		i;
	char	*name;

	i = 0;
	while (i < table->ph_num - 1)
	{
		name = ft_itoa(i + 1);
		init_philosopher(&philosophers[i], name, i, i + 1);
		philosophers[i].limit = table->time_to_die;
		i++;
	}
	init_philosopher(&philosophers[table->ph_num - 1],
		ft_itoa(table->ph_num), table->ph_num - 1, 0);
	philosophers[table->ph_num - 1].limit = table->time_to_die;
}

int	prepare_table(t_table *table, struct timeval start, t_arg *arg)
{
	int	i;

	i = 0;
	if (parse_philo(table, arg) == -1)
		return (-1);
	table->start_time = start;
	pthread_mutex_init(&table->death, NULL);
	pthread_mutex_init(&table->write, NULL);
	table->allowed = 1;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->ph_num);
	table->philos = malloc(sizeof(t_philo) * table->ph_num);
	while (i < table->ph_num)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	call_philosophers(table->philos, table);
	return (0);
}
