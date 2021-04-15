/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vping <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 16:50:32 by vping             #+#    #+#             */
/*   Updated: 2021/04/15 16:51:32 by vping            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/overall.h"

void ft_pwd(void)
{
	char str[100];

	getcwd(str, 100);
	printf("Current dir is %s\n", str);
}
