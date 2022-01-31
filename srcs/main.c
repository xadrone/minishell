/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgyles <jgyles@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 21:29:50 by jgyles            #+#    #+#             */
/*   Updated: 2022/01/21 22:14:06 by jgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	**init_env()
{
	t_env	**tmp;

	tmp = (t_env **)malloc(sizeof(t_env *));
	if (!tmp)
	{
		exit(1);
	}
	return (tmp);
}

// t_env	*add_new_env(char *key, char *sep, char *val)
// {
// 	t_env	*tmp;

// 	tmp = (t_env *)malloc(sizeof(t_env));
// 	if (!tmp)
// 		exit(1);
// 	tmp->key = key;
// 	tmp->sep = sep;
// 	tmp->value = val;
// 	tmp->next = NULL;
// 	return (tmp);
// }

t_env	*init_elem(char *key, char *sep, char *val)
{
	t_env	*elem;

	elem = (t_env *)malloc(sizeof(t_env));
	if (!elem)
		return (NULL);
	elem->key = key;
	elem->sep = sep;
	elem->value = val;
	elem->next = NULL;
	return (elem);
}

void	add_elem(t_env **head, t_env *elem)
{
	t_env	*tmp;

	tmp = *head;
	if (*head)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = elem;
	}
	else
		*head = elem;
}

void	add_env(char *env, t_env **envp)
{
	int		i;
	char	*key;
	char	*sep;
	char	*val;
	// t_env	*tmp;

	i = 0;
	sep = NULL;
	val = NULL;
	// tmp = *envp;
	while (env[i] && (env[i] == '_' || ft_isalnum(env[i])))
	{
		i++;
	}
	key = ft_substr(env, 0, i);
	// printf("key = %s\n", key);
	if (ft_strchr(env, '='))
	{
		sep = ft_substr(env, i, 1);
	}
	// printf("sep = %s\n", sep);
	if (env[i + 1])
	{
		val = ft_strdup(&env[i + 1]);
	}
	// printf("val = %s\n", val);
	add_elem(envp, init_elem(key, sep, val));
	// tmp = *envp;
	// envp = &tmp;
	// if (*envp == NULL)
	// {
	// 	printf("val = %s\n", val);
	// 	*envp = add_new_env(key, sep, val);
	// }
	// else
	// {
	// 	tmp = *envp;
	// 	while (tmp->next != NULL)
	// 	{
	// 		tmp = tmp->next;
	// 	}
	// 	tmp->next = add_new_env(key, sep, val);
	// }
	// // free(key);
	// free(sep);
	// free(val);
}

void	parse_env(char **env, t_env **data)
{
	int	i;
	t_env	*tmp;

	i = -1;
	tmp = *data;
	while (env[++i])
	{
		// printf("%s\n", env[i]);
		add_env(env[i], data);
		tmp = *data;
	}
	data = &tmp;
}

void	print_all(t_env **data, char *flag)
{
	t_env	*elem;

	elem = *data;
	if (!strcmp(flag, "all"))
	{
		while (elem)
		{
			printf("%s %s %s\n", elem->key, elem->sep, elem->value);
			elem = elem->next;
		}
	}
	else
	{
		while (elem->next)
		{
			if (!strcmp(elem->key, flag))
			{
				printf("%s %s %s\n", elem->key, elem->sep, elem->value);
			}
			elem = elem->next;
		}
	}
}

void	increment(t_env *envp)
{
	int	lvl;

	lvl = ft_atoi(envp->value) + 1;
	free(envp->value);
	envp->value = ft_itoa(lvl);
}

void	shlvl_increment(t_env *envp)
{
	t_env	*env;

	env = envp;
	while (env)
	{
		if (!ft_strcmp(env->key, "SHLVL"))
		{
			increment(env);
			break ;
		}
		env = env->next;
	}
}

int	main(int ac, char **av, char **env)
{
	// int i = -1;
	// while(env[++i])
	// 	printf("%s\n", env[i]);
	t_env	*envp;
	(void)av;

	if (ac != 1)
	{
		exit(0);
	}
	parse_env(env, &envp);
	shlvl_increment(envp);
	print_all(&envp, "USER");
	// printf("key = %s sep = %s val = %s\n", envp->key, envp->sep, envp->value);
}
