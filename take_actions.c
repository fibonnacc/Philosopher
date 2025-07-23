/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helfatih <helfatih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:26:11 by helfatih          #+#    #+#             */
/*   Updated: 2025/07/22 18:57:21 by helfatih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	put_down_the_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	update_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meals_lock);
	philo->last_meals = get_time();
	pthread_mutex_unlock(&philo->last_meals_lock);
}

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_lock("%d has taken a fork\n", philo);
		pthread_mutex_lock(philo->right_fork);
		print_lock("%d has taken a fork\n", philo);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_lock("%d has taken a fork\n", philo);
		pthread_mutex_lock(philo->left_fork);
		print_lock("%d has taken a fork\n", philo);
	}
}

int	check_and_unlock1(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_check);
	if (philo->data->someone_died)
	{
		pthread_mutex_unlock(&philo->data->death_check);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->death_check);
	return (0);
}

int	check_and_unlock2(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_check);
	if (philo->data->someone_died)
	{
		pthread_mutex_unlock(&philo->data->death_check);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->death_check);
	return (0);
}
