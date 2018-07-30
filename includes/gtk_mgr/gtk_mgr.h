/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_mgr.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 21:18:21 by adleau            #+#    #+#             */
/*   Updated: 2018/07/30 07:05:22 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GTK_MGR_H
# define GTK_MGR_H
# include <gtk/gtk.h>
# define NB_WINDOWS 7
# define BASE_WIN 0
# define MAIN_WIN 1
# define ADD_POPUP 2
# define FILTER_POPUP 3
# define EDIT_POPUP 4
# define EXPORT_POPUP 5
# define OPEN_FILE 6

typedef struct			s_window
{
	GtkWidget			*win;
	GtkWidget			**buttons;
}						t_window;

typedef struct			s_gtk_mgr
{
	int					active_win;
	GtkBuilder			*builder;
	t_window			*windows;
	cairo_surface_t		*pixmap;
	unsigned char		*data;
}						t_gtk_mgr;

#endif
