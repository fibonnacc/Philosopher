/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helfatih <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 21:47:02 by helfatih          #+#    #+#             */
/*   Updated: 2025/07/29 21:47:22 by helfatih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_lock(char *format, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_check);
	if (philo->data->someone_died)
	{
		pthread_mutex_unlock(&philo->data->death_check);
		return ;
	}
	pthread_mutex_unlock(&philo->data->death_check);
	pthread_mutex_lock(&philo->data->writing);
	printf("%ld ", get_time() - philo->data->start_time);
	printf(format, philo->id);
	pthread_mutex_unlock(&philo->data->writing);
}

void	ft_usleep(long time, t_philo *philo)
{
	long	start;

	start = get_time();
	while (time >= get_time() - start)
	{
		pthread_mutex_lock(&philo->data->death_check);
		if (philo->data->someone_died)
		{
			pthread_mutex_unlock(&philo->data->death_check);
			return ;
		}
		pthread_mutex_unlock(&philo->data->death_check);
		usleep(1000);
	}
}

void	*make_simulation(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2)
		usleep(3000);
	while (1)
	{
		if ((check_and_unlock2(philo)) == 1)
			return (NULL);
		take_forks(philo);
		update_last_meal(philo);
		print_lock("%d is eating\n", philo);
		pthread_mutex_lock(&philo->last_meals_lock);
		philo->meal_count++;
		pthread_mutex_unlock(&philo->last_meals_lock);
		ft_usleep(philo->data->time_to_eat, philo);
		if ((check_and_unlock1(philo)) == 1)
			return (NULL);
		put_down_the_forks(philo);
		print_lock("%d is sleeping\n", philo);
		ft_usleep(philo->data->time_to_sleep, philo);
		print_lock("%d is thinking\n", philo);
		condition_1(philo);
	}
	return (NULL);
}

void	*monitore_deaths(void *arg)
{
	t_data	*data;
	int		i;
	int		enough;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		enough = 1;
		while (i < data->num_philosopher)
		{
			if ((check_if_someone_death(data, &i)) == 1)
				return (NULL);
			pthread_mutex_lock(&data->philo[i].last_meals_lock);
			if (data->philo[i].meal_count < data->num_of_times_to_eat)
				enough = 0;
			pthread_mutex_unlock(&data->philo[i].last_meals_lock);
			i++;
		}
		if (check_if_all_eat(data, &enough) == 1)
			return (NULL);
		usleep(500);
	}
	return (NULL);
}

int	creat_thread(t_data *data)
{
	int			i;
	pthread_t	monitor;

	i = 0;
	while (i < data->num_philosopher)
	{
		if (check_and_creat_thread(data, &i) == 1)
			return (1);
		i++;
	}
	if (pthread_create(&monitor, NULL, monitore_deaths, data) != 0)
		return (1);
	if (pthread_join(monitor, NULL) != 0)
		return (1);
	i = 0;
	while (i < data->num_philosopher)
	{
		if (pthread_join(data->philo[i].thread, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}
