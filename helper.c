/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helfatih <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 21:47:33 by helfatih          #+#    #+#             */
/*   Updated: 2025/07/29 21:47:39 by helfatih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	long	res;
	int		i;
	int		s;

	i = 0;
	res = 0;
	s = 1;
	if (!str)
		return (-1);
	if (str[i] == '+')
	{
		s = 1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		if (res > INT_MAX || res < INT_MIN)
			return (-1);
		i++;
	}
	return ((int)(res * s));
}

int	is_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		return (1);
	if (str[i] == '+')
	{
		i++;
	}
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_if_someone_death(t_data *data, int *i)
{
	long	current_time;

	pthread_mutex_lock(&data->philo[*i].last_meals_lock);
	current_time = get_time() - data->philo[*i].last_meals;
	pthread_mutex_unlock(&data->philo[*i].last_meals_lock);
	if ((current_time) >= data->time_to_die)
	{
		pthread_mutex_lock(&data->writing);
		printf("%ld %d died\n", (get_time() - data->start_time),
			data->philo[*i].id);
		pthread_mutex_unlock(&data->writing);
		pthread_mutex_lock(&data->death_check);
		data->someone_died = 1;
		pthread_mutex_unlock(&data->death_check);
		return (1);
	}
	return (0);
}

void	init_small_data(t_data *data, char **av)
{
	data->num_philosopher = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		data->num_of_times_to_eat = ft_atoi(av[5]);
	pthread_mutex_init(&(data->writing), NULL);
	pthread_mutex_init(&(data->death_check), NULL);
	pthread_mutex_init(&(data->check), NULL);
}

int	check_and_creat_thread(t_data *data, int *i)
{
	if (data->num_philosopher == 1)
	{
		pthread_mutex_lock(&data->writing);
		printf("%ld philo %d died\n", (get_time() - data->start_time),
			data->philo[*i].id);
		pthread_mutex_unlock(&data->writing);
		return (1);
	}
	if (pthread_create(&(data->philo[*i].thread), NULL, make_simulation,
			&data->philo[*i]) != 0)
	{
		return (1);
	}
	return (0);
}
