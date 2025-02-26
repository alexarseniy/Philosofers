/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <olarseni@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 00:43:55 by olarseni          #+#    #+#             */
/*   Updated: 2025/02/26 00:49:11 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	check_death(t_data *data, int i)
{
	size_t	time;

	time = get_time();
	pthread_mutex_lock(&data->death);
	if (data->t2die < time - data->philos[i].last_eat)
	{
		pthread_mutex_unlock(&data->death);
		action(DIE, SDIE, &data->philos[i]);
		pthread_mutex_lock(&data->death);
		data->finish = true;
		pthread_mutex_unlock(&data->death);
	}
	else
		pthread_mutex_unlock(&data->death);
}

void	*monitoring(void *arg)
{
	int		i;
	t_data	*data;

	data = (t_data *)arg;
	i = 0;
	while (!is_over(data))
	{
		if (i == data->n_philos)
			i = 0;
		check_death(data, i);
		i++;
	}
	return (arg);
}
