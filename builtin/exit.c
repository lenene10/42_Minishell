/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwechsle <fwechsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:40:12 by fwechsle          #+#    #+#             */
/*   Updated: 2024/01/24 19:24:47 by fwechsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

long	ft_atoi_long(const char *str)
{
	int			i;
	long long	result;
	long long	pre;

	pre = 1;
	i = 0;
	result = 0;
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			pre *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * pre);
}

int	check_for_number(char *arg)
{
	int	n;

	n = 0;
	if (arg[0] == '-' || arg[0] == '+')
		n++;
	while (arg[n])
	{
		if ((arg[n] < '0' || arg[n] > '9'))
			return (1);
		n++;
	}
	return (0);
}

int	exit_too_many(int pid_check)
{
	if (pid_check == 1)
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
	else
		ft_putstr_fd("exit\nexit: too many arguments\n", STDERR_FILENO);
	return (1);
}

int	exit_not_numeric(int pid_check, t_list *tokens, t_list **env_copy)
{
	if (pid_check == 1)
	{
		ft_putstr_fd("exit: numeric argumend required\n", STDERR_FILENO);
		return (2);
	}
	else
	{
		ft_putstr_fd("exit: numeric argument required\n", STDERR_FILENO);
		if (env_copy)
			ft_lstclear(env_copy, free);
		rl_clear_history();
	}
	if (tokens)
		ft_free_parser(tokens);
	exit (2);
}

int	exit_with_number(int pid_check, char *numb, t_list *tokens, \
	t_list **env_copy)
{
	unsigned char	c;

	if (pid_check == 0)
	{
		printf("exit\n");
		if (env_copy)
			ft_lstclear(env_copy, free);
		rl_clear_history();
	}
	c = ft_atoi_long(numb);
	if (pid_check == 1)
		return (c);
	if (tokens)
		ft_free_parser(tokens);
	exit (c);
}
