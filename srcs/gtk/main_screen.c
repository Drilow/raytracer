/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 15:18:24 by adleau            #+#    #+#             */
/*   Updated: 2018/07/22 15:57:38 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <unistd.h>
#include <libft.h>
#define MAIN_WIN g_global.gtk_mgr.main_win
#define BUTTONS g_global.gtk_mgr.grid.buttons

extern t_global g_global;



void			main_screen(GtkApplication *app, gpointer __attribute__((unused))user_data)
{
	GtkWidget	*header;

	(void)app;
	gtk_widget_destroy(g_global.gtk_mgr.grid.grid);
	header = gtk_header_bar_new();
	gtk_container_add(GTK_CONTAINER(MAIN_WIN), header);
	gtk_widget_show_all(MAIN_WIN);
	printf("aaaa\n");
}
