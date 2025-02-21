/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <olarseni@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 21:38:20 by olarseni          #+#    #+#             */
/*   Updated: 2025/02/21 23:06:45 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	validate_arg(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i] && arg[i] >= '0' && arg[i] <= '9')
		i++;
	if (arg[i])
		return (false);
	return (true);
}

bool	is_valid_args(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6 || !argv)
		return (false);
	while (argv[i] && validate_arg(argv[i]))
		i++;
	if (argv[i])
		return (false);
	return (true);
}
