/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <olarseni@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 23:15:18 by olarseni          #+#    #+#             */
/*   Updated: 2025/02/21 21:40:28 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>
# include <pthread.h>

typedef pthread_mutex_t	t_mutex;
typedef pthread_t		t_thrd;

typedef struct s_philo
{
	int				id;
	int				n_eats;
	volatile bool	is_alive;
	volatile size_t	last_eat;
	t_mutex			*fork;
	t_mutex			death;
}	t_philo;

typedef struct s_data
{
	int				n_philos;
	volatile bool	finish;
	size_t			t2die;
	size_t			t2eat;
	size_t			t2sleep;
	int				n_eats;
	t_mutex			*forks;
	t_mutex			print;
	t_philo			*philos;
}	t_data;

bool is_valid_args(int argc, char **argv);

#endif
