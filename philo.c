/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helfatih <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 21:48:11 by helfatih          #+#    #+#             */
/*   Updated: 2025/07/29 21:48:13 by helfatih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_my_argument(char **av)
{
	if (ft_atoi(av[1]) > NUM_PHILO || is_number(av[1]) == 1)
		return (write(2, "the number of philosophers is invalid\n", 38), 1);
	if (ft_atoi(av[2]) <= 0 || is_number(av[2]) == 1)
		return (write(2, "time_to_die is invalid\n", 23), 1);
	if (ft_atoi(av[3]) <= 0 || is_number(av[3]) == 1)
		return (write(2, "time_to_eat is invalid\n", 23), 1);
	if (ft_atoi(av[4]) <= 0 || is_number(av[4]) == 1)
		return (write(2, "time_to_sleep is invalid\n", 25), 1);
	if (av[5])
	{
		if (ft_atoi(av[5]) <= 0 || is_number(av[5]) == 1)
			return (write(2,
					"number_of_times_each_philosopher_must_eat is invalid\n",
					53), 1);
	}
	return (0);
}

int	check_if_all_eat(t_data *data, int *enough)
{
	if (data->num_of_times_to_eat > 0 && *enough == 1)
	{
		pthread_mutex_lock(&data->death_check);
		data->someone_died = 1;
		pthread_mutex_unlock(&data->death_check);
		return (1);
	}
	return (0);
}

void	clean_all(t_data *data)
{
	int	i;

	if (data->philo)
	{
		free(data->philo);
	}
	if (data->forks)
	{
		i = 0;
		while (i < data->num_philosopher)
		{
			pthread_mutex_destroy(&(data->forks[i]));
			i++;
		}
		free(data->forks);
	}
	pthread_mutex_destroy(&(data->writing));
	pthread_mutex_destroy(&(data->death_check));
	pthread_mutex_destroy(&(data->check));
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5 || ac > 6)
		return (write(2, "the number of argument is invalid\n", 34), 1);
	if (check_my_argument(av) == 1)
	{
		return (1);
	}
	if (initialize_data(&data, ac, av) == 1)
		return (1);
	initialize_philosophers(&data);
	if (creat_thread(&data) == 1)
	{
		return (1);
	}
	clean_all(&data);
}
