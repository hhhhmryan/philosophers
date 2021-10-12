/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mryan <mryan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 19:27:12 by mryan             #+#    #+#             */
/*   Updated: 2021/07/28 16:21:19 by mryan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	message_2(t_table *table, char *philo_name, char *cont)
{
	if (strcmp(cont, "die") == 0 && (table->allowed == 1))
	{
		printf("\x1b[31m[%ld] %s DIED\x1b[0m\n",
			get_time_int(table), philo_name);
		pthread_mutex_unlock(&table->write);
		return (0);
	}
	if (strcmp(cont, "dinner is done") == 0 && (table->allowed == 1))
	{
		printf("\x1b[32m[%ld] philosophers finished their dinner\x1b[0m\n",
			get_time_int(table));
		pthread_mutex_unlock(&table->write);
		return (0);
	}
	return (1);
}

int	message(t_table *table, char *philo_name, char *cont)
{
	if (table->allowed == 1)
	{
		pthread_mutex_lock(&table->write);
		if ((strcmp(cont, "left fork") == 0) && (table->allowed == 1))
			printf("[%ld] %s has taken left fork\n",
				get_time_int(table), philo_name);
		else if ((strcmp(cont, "right fork") == 0) && (table->allowed == 1))
			printf("[%ld] %s has taken right fork\n",
				get_time_int(table), philo_name);
		else if ((strcmp(cont, "eat") == 0) && (table->allowed == 1))
			printf("[%ld] %s is eating\n", get_time_int(table), philo_name);
		else if ((strcmp(cont, "sleep") == 0) && (table->allowed == 1))
			printf("[%ld] %s is sleeping\n", get_time_int(table), philo_name);
		else if ((strcmp(cont, "think") == 0) && (table->allowed == 1))
			printf("[%ld] %s is thinking\n", get_time_int(table), philo_name);
		else if (message_2(table, philo_name, cont) == 0
			&& (table->allowed == 1))
			return (0);
		pthread_mutex_unlock(&table->write);
		return (1);
	}
	else
		return (0);
}
