/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/08 11:38:18 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/02/10 11:24:34 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleep(int time)
{
	long	start;
	long	elapsed;

	start = find_ms();
	elapsed = 0;
	while (elapsed < time)
	{
		usleep(time * 1000);
		elapsed = find_ms() - start;
	}
}

int	determine_r_fork(t_philo *philo)
{
	if (philo->id == 0)
		return (philo->tools->num_p - 1);
	else
		return (philo->id - 1);
}

int	ft_eat(t_philo *philo)
{
	int	r_fork;

	r_fork = determine_r_fork(philo);
	pthread_mutex_lock(&philo->tools->forks[r_fork]);
	print_lock("has picked up a 🤛fork", philo->id, philo->tools,
		elapsed(philo->tools->start_time));
	pthread_mutex_lock(&philo->tools->forks[philo->id]);
	print_lock("has picked up a 🤛fork🤜", philo->id, philo->tools,
		elapsed(philo->tools->start_time));
	set_m_t(philo);
	philo->c_meals--;
	print_lock("is eating 🍝", philo->id, philo->tools,
		elapsed(philo->tools->start_time));
	ft_sleep(philo->tools->time_e);
	pthread_mutex_unlock(&philo->tools->forks[r_fork]);
	pthread_mutex_unlock(&philo->tools->forks[philo->id]);
	return (1);
}

void	*life(void *tmp)
{
	t_philo			*philo;

	philo = tmp;
	if (philo->id % 2 == 0)
		usleep(philo->tools->time_e * 1000);
	while (!check_end(philo->tools) && philo->c_meals != 0)
	{
		print_lock("is thinking 🤔", philo->id, philo->tools,
			elapsed(philo->tools->start_time));
		ft_eat(philo);
		print_lock("is sleeping 💤", philo->id, philo->tools,
			elapsed(philo->tools->start_time));
		ft_sleep(philo->tools->time_s);
	}
	return (NULL);
}
