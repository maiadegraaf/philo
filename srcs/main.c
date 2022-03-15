/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 11:49:14 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/02/10 13:37:06 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	malloc_philo_and_forks(t_tools *tools)
{
	if (pthread_mutex_init(&tools->status, NULL))
		return (0);
	if (pthread_mutex_init(&tools->meal_time, NULL))
		return (0);
	tools->philo = malloc(sizeof(t_philo) * tools->num_p);
	if (!tools->philo)
		return (0);
	tools->forks = malloc(sizeof(pthread_mutex_t) * tools->num_p);
	if (!tools->forks)
	{
		free(tools->philo);
		return (0);
	}
	return (1);
}

int	create_philo(t_tools *tools, int i)
{
	tools->philo[i].id = i;
	tools->philo[i].time_last_meal = find_ms();
	tools->philo[i].tools = tools;
	tools->philo[i].c_meals = tools->num_e;
	if (pthread_create(&tools->philo[i].thread, NULL, &life, &tools->philo[i]))
		return (1);
	return (0);
}

int	init_philo_and_forks(t_tools *tools)
{
	int	i;

	if (!malloc_philo_and_forks(tools))
		return (0);
	i = 0;
	while (i < tools->num_p)
	{
		if (pthread_mutex_init(&tools->forks[i++], NULL))
		{
			free_philo_and_forks(tools);
			return (0);
		}
	}
	i = 0;
	while (i < tools->num_p)
	{
		if (create_philo(tools, i))
		{
			free_philo_and_forks(tools);
			return (0);
		}
		i++;
	}
	return (1);
}

int	parse_arg(int argc, char **argv, t_tools *tools)
{
	tools->num_p = 0;
	tools->num_e = 0;
	tools->time_d = 0;
	tools->time_e = 0;
	tools->time_s = 0;
	tools->start_time = find_ms();
	tools->end = false;
	if (ft_atoi(argv[0], &tools->num_p)
		|| ft_atoi(argv[1], &tools->time_d)
		|| ft_atoi(argv[2], &tools->time_e)
		|| ft_atoi(argv[3], &tools->time_s))
		return (0);
	if (tools->num_p < 1)
		return (0);
	if (argc == 5)
	{
		if (ft_atoi(argv[4], &tools->num_e))
			return (0);
	}
	else
		tools->num_e = -1;
	return (1);
}

int	main(int argc, char **argv)
{
	t_tools	tools;

	if (argc != 5 && argc != 6)
	{
		printf("Incorrect number of arguments\n");
		return (0);
	}
	if (!parse_arg(--argc, ++argv, &tools))
	{
		printf("Incorrect input type\n");
		return (0);
	}
	if (!init_philo_and_forks(&tools))
	{
		printf("Malloc Error\n");
		return (0);
	}
	monitoring_wrapper(&tools);
	join_threads(&tools);
}
