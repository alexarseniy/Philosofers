/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <olarseni@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 23:15:18 by olarseni          #+#    #+#             */
/*   Updated: 2025/02/26 00:50:01 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define SFORK "takes a fork🍴"
# define SEAT "is eating🍝😛"
# define SSLEEP "is sleeping😴"
# define STHINK "is thinking🎓"
# define SDIE "is dead💩👻"

typedef pthread_mutex_t	t_mutex;
typedef pthread_t		t_thread;

typedef enum e_action
{
	FORK = 0,
	EAT,
	SLEEP,
	THINK,
	DIE
}	t_enum;

typedef struct s_philo
{
	int				id;
	int				n_eats;
	volatile size_t	last_eat;
	t_mutex			*lfork;
	t_mutex			*rfork;
	t_thread		philo;
	struct s_data	*data;
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
	t_mutex			death;
	t_philo			*philos;
}	t_data;

bool	is_valid_args(int argc, char **argv);
t_data	*init_data(int argc, char **argv);
t_mutex	*init_forks(int n);
t_philo	*init_philos(int n, t_mutex *forks, t_data *data);
void	destroy_data(t_data *data);
void	destroy_forks(t_mutex *forks, int n);
void	destroy_philos(t_philo *philos, int n);
size_t	ft_atos(char *s);
size_t	get_time(void);
void	*routine(void *arg);
void	*monitoring(void *arg);
bool	is_over(t_data *data);
void	action(int action, char *s, t_philo *philo);

#endif
