/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <olarseni@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 23:23:44 by olarseni          #+#    #+#             */
/*   Updated: 2025/02/25 00:58:02 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*init_philos(int n, t_mutex *forks, t_data *data)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * n);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < n)
	{
		philos[i].data = data;
		philos[i].id = i + 1;
		philos[i].n_eats = 0;
		philos[i].last_eat = 0;
		philos[i].lfork = &forks[i];
		philos[i].rfork = &forks[(i + 1) % n];
		i++;
	}
	return (philos);
}

t_mutex	*init_forks(int n)
{
	t_mutex	*forks;
	int		i;
	int		n_tries;

	forks = malloc(sizeof(t_mutex) * n);
	if (!forks)
		return (0);
	i = 0;
	n_tries = 3;
	while (i < n)
	{
		if (pthread_mutex_init(&forks[i], NULL) && n_tries)
		{
			n_tries--;
			continue ;
		}
		else if (!n_tries)
			return (destroy_forks(forks, i), NULL);
		else
			n_tries = 3;
		i++;
	}
	return (forks);
}

static void	*init_forks_philos(t_data *data)
{
	data->forks = init_forks(data->n_philos);
	if (!data->forks)
		return (free(data), NULL);
	if (pthread_mutex_init(&(data->print), NULL))
		return (destroy_data(data), NULL);
	data->philos = init_philos(data->n_philos, data->forks, data);
	if (!data->philos)
		return (destroy_data(data), NULL);
	return (data);
}

t_data	*init_data(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->n_philos = ft_atos(argv[1]);
	data->finish = false;
	data->t2die = ft_atos(argv[2]);
	data->t2eat = ft_atos(argv[3]);
	data->t2sleep = ft_atos(argv[4]);
	if (argc == 6)
		data->n_eats = ft_atos(argv[5]);
	else
		data->n_eats = -1;
	data->forks = NULL;
	data->philos = NULL;
	if(!init_forks_philos(data))
		return (NULL);
	if (pthread_mutex_init(&data->death, NULL))
		return (destroy_data(data), NULL);
	return (data);
}

