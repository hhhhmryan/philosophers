/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mryan <mryan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 16:01:30 by mryan             #+#    #+#             */
/*   Updated: 2021/07/28 16:28:25 by mryan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	start_philo(t_table *table, t_arg *arg)
{
	struct timeval	start_time;

	gettimeofday(&start_time, NULL);
	if (prepare_table(table, start_time, arg) == -1)
		return (-1);
	return (0);
}

void	put_args(t_table *table, t_philo_struct *args)
{
	int	i;

	i = 0;
	while (i < table->ph_num)
	{
		args[i].table = table;
		args[i].philosopher = &(table->philos[i]);
		i++;
	}
}

int	main_threads(t_table *table, t_philo_struct *args, pthread_t *threads)
{
	int			i;
	pthread_t	checker;

	put_args(table, args);
	i = 0;
	while (i < table->ph_num)
	{
		args[i].philosopher->index = i;
		if (pthread_create(&threads[i], NULL, cycle, &args[i]) != 0)
			return (1);
		i++;
	}
	if (pthread_create(&checker, NULL, monitor, table) != 0)
		return (1);
	i = 0;
	while (i < table->ph_num)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	return (0);
}

void	free_philos(t_table *table, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < table->ph_num)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	if (table->philos)
		free(table->philos);
	if (threads)
		free(threads);
}

int	main(int argc, char **argv)
{
	pthread_t		*threads;
	t_philo_struct	*args;
	t_table			table;
	t_arg			arg;

	arg.argc = argc;
	arg.argv = argv;
	if (start_philo(&table, &arg) == -1)
		return (-1);
	threads = malloc(sizeof(pthread_t) * table.ph_num);
	if (!threads)
		return (1);
	args = malloc(sizeof(t_philo_struct) * table.ph_num);
	if (!args)
		return (1);
	if (main_threads(&table, args, threads) == 1)
		return (1);
	free_philos(&table, threads);
	return (0);
}
