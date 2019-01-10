/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_properly.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 18:24:04 by adleau            #+#    #+#             */
/*   Updated: 2019/01/10 18:26:35 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>

extern t_global g_global;

void				exit_properly(int ret)
{
	if (g_global.r->objects)
		free(objects(g_global.r->objects));
	gtk_main_quit();
	exit(ret);
}

