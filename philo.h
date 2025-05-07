/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helfatih <helfatih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 09:10:57 by helfatih          #+#    #+#             */
/*   Updated: 2025/04/22 09:37:39 by helfatih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define NUM_PHILO 400

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <string.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				id;
	int				meal_count;
	long			last_meals;
	pthread_mutex_t	last_meals_lock;
	pthread_t		thread;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				num_philosopher;
	long			time_to_die;
	int				time_to_eat;
	int				someone_died;
	int				time_to_sleep;
	int				num_of_times_to_eat;
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	writing;
	pthread_mutex_t	check;
	pthread_mutex_t	death_check;
	t_philo			*philo;
}					t_data;

int					ft_atoi(char *str);
int					is_number(char *str);
int					check_my_argument(char **av);
int					initialize_data(t_data *data, int ac, char **av);
void				initialize_philosophers(t_data *data);
int					creat_thread(t_data *data);
void				*my_routine(void *arg);
long				get_time(void);
void				clean_all(t_data *data);
void				*monitore_deaths(void *arg);
void				take_forks(t_philo *philo);
void				update_last_meal(t_philo *philo);
void				put_down_the_forks(t_philo *philo);
void				print_lock(char *format, t_philo *philo);
int					check_and_unlock1(t_philo *philo);
int					check_and_unlock2(t_philo *philo);
int					check_if_someone_death(t_data *data, int *i);
void				init_small_data(t_data *data, char **av);
int					check_and_creat_thread(t_data *data, int *i);
int					check_if_all_eat(t_data *data, int *enough);

#endif