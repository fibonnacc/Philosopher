/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helfatih <helfatih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 11:36:09 by helfatih          #+#    #+#             */
/*   Updated: 2025/07/24 09:58:16 by helfatih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	initialize_data(t_data *data, int ac, char **av)
{
	int	i;

	(void)ac;
	memset(data, 0, sizeof(t_data));
	init_small_data(data, av);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philosopher);
	if (!data->forks)
		return (1);
	data->philo = malloc(sizeof(t_philo) * data->num_philosopher);
	if (!data->philo)
	{
		free(data->forks);
		return (1);
	}
	i = 0;
	while (i < data->num_philosopher)
	{
		pthread_mutex_init(&(data->forks[i]), NULL);
		i++;
	}
	return (0);
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	condition_1(t_philo *philo)
{
	if (philo->data->num_philosopher % 2)
	{
		if (philo->id % 2)
		{
			if (philo->data->time_to_eat >= philo->data->time_to_sleep)
				usleep((philo->data->time_to_eat - philo->data->time_to_sleep
						+ 10) * 1000);
		}
	}
}

void	initialize_philosophers(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time();
	data->someone_died = 0;
	while (i < data->num_philosopher)
	{
		data->philo[i].meal_count = 0;
		data->philo[i].left_fork = &data->forks[i];
		data->philo[i].right_fork = &data->forks[(i + 1)
			% data->num_philosopher];
		data->philo[i].id = i + 1;
		data->philo[i].last_meals = data->start_time;
		data->philo[i].data = data;
		pthread_mutex_init(&(data->philo[i].last_meals_lock), NULL);
		i++;
	}
}
