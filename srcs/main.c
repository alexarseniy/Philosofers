/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <olarseni@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 23:14:58 by olarseni          #+#    #+#             */
/*   Updated: 2025/02/25 01:07:21 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_over(t_data *data)
{
	bool	flag;

	pthread_mutex_lock(&data->death);
	flag = data->finish;
	pthread_mutex_unlock(&data->death);
	return (flag);
}

void *routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(philo->data->t2eat * 0.5);
	while (!is_over(philo->data))
	{
		pthread_mutex_lock(&philo->data->print);
		printf("%zu %i is eating\n", get_time(), philo->id);
		philo->last_eat = get_time();
		pthread_mutex_unlock(&philo->data->print);
		usleep(philo->data->t2eat * 1000);
		pthread_mutex_lock(&philo->data->print);
		printf("%zu %i is sleeping\n", get_time(), philo->id);
		pthread_mutex_unlock(&philo->data->print);
		usleep(philo->data->t2sleep * 1000);
		pthread_mutex_lock(&philo->data->print);
		printf("%zu %i is thinking\n", get_time(), philo->id);
		pthread_mutex_unlock(&philo->data->print);
	}
	return (arg);
}

void	*monitoring(void *arg)
{
	int		i;
	t_data	*data;
	size_t	time;

	data = (t_data *)arg;
	i = 0;
	while (!is_over(data))
	{
		if (i == data->n_philos)
			i = 0;
		time = get_time();
		pthread_mutex_lock(&data->print);
		if (data->t2die < time - data->philos[i].last_eat)
		{
			printf("%zu %d died\n", time, data->philos[i].id);
			pthread_mutex_unlock(&data->print);
			pthread_mutex_lock(&data->death);
			data->finish = true;
			pthread_mutex_unlock(&data->death);
		}
		else
			pthread_mutex_unlock(&data->print);
		i++;
	}
	return (arg);
}

int	start(t_data *data)
{
	t_thread	monitor;
	int			i;

	i = 0;
	while (i < data->n_philos)
	{
		data->philos[i].last_eat = get_time();
		if (pthread_create(&(data->philos[i].philo), NULL, routine,
					&(data->philos[i])))
			return (-1);
		i++;
	}
	i = 0;
	if (pthread_create(&monitor, NULL, &monitoring, data))
		return (-1);
	while (i < data->n_philos)
	{
		if (pthread_join(data->philos[i].philo, NULL))
			return (-1);
		i++;
	}
	pthread_mutex_lock(&data->death);
	data->finish = true;
	pthread_mutex_unlock(&data->death);
	pthread_join(monitor, NULL);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (!is_valid_args(argc, argv))
		return (printf("ERROR: Invalid args\n"));
	data = init_data(argc, argv);
	if (!data)
		return (printf("ERROR: Failed init program data\n"));
	if (start(data))
		return (destroy_data(data), printf("ERROR: Failed execution\n"));
	destroy_data(data);
	return (0);
}
