/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <olarseni@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 23:14:58 by olarseni          #+#    #+#             */
/*   Updated: 2025/02/26 01:06:51 by olarseni         ###   ########.fr       */
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

void	action(int action, char *s, t_philo *philo)
{
	size_t	time;

	if (!is_over(philo->data) && philo->n_eats != philo->data->n_eats)
	{
		pthread_mutex_lock(&philo->data->print);
		time = get_time();
		printf("%zu %i %s\n", time, philo->id, s);
		pthread_mutex_unlock(&philo->data->print);
		if (action == EAT)
		{
			pthread_mutex_lock(&philo->data->death);
			philo->last_eat = time;
			philo->n_eats++;
			pthread_mutex_unlock(&philo->data->death);
		}
	}
}

static int	start_philos(t_data *data)
{
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
	return (0);
}

int	start(t_data *data)
{
	int			i;
	t_thread	monitor;

	i = 0;
	if (start_philos(data))
		return (-1);
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
	if (data->n_philos == 1)
	{
		action(FORK, SFORK, data->philos);
		usleep(data->t2die * 1000);
		action(DIE, SDIE, data->philos);
	}
	if (!data)
		return (printf("ERROR: Failed init program data\n"));
	if (data->n_philos > 1 && start(data))
		return (destroy_data(data), printf("ERROR: Failed execution\n"));
	destroy_data(data);
	return (0);
}
