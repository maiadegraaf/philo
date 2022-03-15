/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mutex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/08 10:00:59 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/02/10 12:05:54 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_end(t_tools *tools)
{
	int	status;

	pthread_mutex_lock(&tools->status);
	if (tools->end)
		status = 1;
	else
		status = 0;
	pthread_mutex_unlock(&tools->status);
	return (status);
}

void	change_end(t_tools *tools)
{
	pthread_mutex_lock(&tools->status);
	tools->end = true;
	pthread_mutex_unlock(&tools->status);
}

void	set_m_t(t_philo *philo)
{
	pthread_mutex_lock(&philo->tools->meal_time);
	philo->time_last_meal = find_ms();
	pthread_mutex_unlock(&philo->tools->meal_time);
}

long	read_m_t(t_philo *philo)
{
	long	last_meal_time;

	pthread_mutex_lock(&philo->tools->meal_time);
	last_meal_time = philo->time_last_meal;
	pthread_mutex_unlock(&philo->tools->meal_time);
	return (last_meal_time);
}
