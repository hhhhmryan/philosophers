/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mryan <mryan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 12:12:53 by mryan             #+#    #+#             */
/*   Updated: 2021/07/28 19:19:39 by mryan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*monitor(void *arg)
{
	t_table			*table;
	t_philo			*philo;
	int				i;
	int				temp;

	table = (t_table *)arg;
	while (table->allowed)
	{
		i = 0;
		while (i < table->ph_num)
		{
			philo = &table->philos[i];
			temp = get_time_int(table);
			if (temp > philo->limit)
			{
				message(table, philo->name, "die");
				table->allowed = 0;
				forks_unlock(table);
				return ((void *)0);
			}
			i++;
		}
		usleep(50);
	}
	return ((void *)0);
}
