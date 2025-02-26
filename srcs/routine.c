/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <olarseni@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 00:42:09 by olarseni          #+#    #+#             */
/*   Updated: 2025/02/26 00:43:15 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	routine_eat(t_philo *philo)
{
	if (philo->id % philo->data->n_philos)
	{
		pthread_mutex_lock(philo->lfork);
		action(FORK, SFORK, philo);
		pthread_mutex_lock(philo->rfork);
		action(FORK, SFORK, philo);
	}
	else
	{
		pthread_mutex_lock(philo->rfork);
		action(FORK, SFORK, philo);
		pthread_mutex_lock(philo->lfork);
		action(FORK, SFORK, philo);
	}
	action(EAT, SEAT, philo);
	pthread_mutex_unlock(philo->rfork);
	pthread_mutex_unlock(philo->lfork);
	usleep(philo->data->t2eat * 1000);
}

static void	routine_sleep_think(t_philo *philo)
{
	action(SLEEP, SSLEEP, philo);
	usleep(philo->data->t2sleep * 1000);
	action(THINK, STHINK, philo);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!is_over(philo->data) && philo->n_eats != philo->data->n_eats)
	{
		routine_eat(philo);
		routine_sleep_think(philo);
	}
	return (arg);
}
