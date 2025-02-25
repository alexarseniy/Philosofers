/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <olarseni@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 23:24:37 by olarseni          #+#    #+#             */
/*   Updated: 2025/02/24 23:32:22 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_forks(t_mutex *forks, int n)
{
	while (n)
	{
		pthread_mutex_destroy(&(forks[n - 1]));
		n--;
	}
	free(forks);
}

void	destroy_philos(t_philo *philos, int n)
{
	while (n)
	{
		pthread_mutex_destroy(&philos[n - 1].death);
		n--;
	}
	free(philos);
}

void	destroy_data(t_data *data)
{
	int	i;

	if (data->forks)
	{
		destroy_forks(data->forks, data->n_philos);
		data->forks = NULL;
	}
	i = 0;
	if (data->philos)
	{
		destroy_philos(data->philos, data->n_philos);
		data->philos = NULL;
	}
	pthread_mutex_destroy(&data->print);
	free(data);
}
