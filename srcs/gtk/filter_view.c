/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_view.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 07:36:43 by adleau            #+#    #+#             */
/*   Updated: 2019/01/16 10:56:30 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <fcntl.h>
#include <libft.h>

extern t_global		g_global;

void				handle_filter_validation(void)
{
	int		r;

	gtk_widget_show_all(FILTER_VIEW.win);
	r = gtk_dialog_run(GTK_DIALOG(FILTER_VIEW.win));
	if (r == GTK_RESPONSE_ACCEPT)
	{
		gtk_widget_destroy(FILTER_VIEW.win);
		redraw(false);
	}
	else if (r == GTK_RESPONSE_REJECT)
	{
		free(GTKMGR.buf);
		GTKMGR.buf = NULL;
		GTKMGR.buf
		= ft_ustrdup(GTKMGR.saved,
		WIN_H * cairo_format_stride_for_width(CAIRO_FORMAT_RGB24, WIN_W));
		gtk_widget_destroy(FILTER_VIEW.win);
		redraw(true);
	}
}

void				deactivate_filter_buttons(GtkWidget *except)
{
	if (&(FILTER_VIEW.bw_button) != &except)
		gtk_widget_set_state_flags(FILTER_VIEW.bw_button,
		GTK_STATE_FLAG_NORMAL, true);
	if (&(FILTER_VIEW.sepia_button) != &except)
		gtk_widget_set_state_flags(FILTER_VIEW.sepia_button,
		GTK_STATE_FLAG_NORMAL, true);
	if (&(FILTER_VIEW.reversed_button) != &except)
		gtk_widget_set_state_flags(FILTER_VIEW.reversed_button,
		GTK_STATE_FLAG_NORMAL, true);
}

void				handle_filters(GtkButton *button)
{
	int				x;
	int				y;
	int				stride;
	void			(*f)(unsigned char*);

	if (button == GTK_BUTTON(FILTER_VIEW.bw_button))
		f = black_white;
	else if (button == GTK_BUTTON(FILTER_VIEW.sepia_button))
		f = sepia;
	else if (button == GTK_BUTTON(FILTER_VIEW.reversed_button))
		f = reversed;
	deactivate_filter_buttons((GtkWidget*)button);
	stride = cairo_format_stride_for_width(CAIRO_FORMAT_RGB24, WIN_W);
	y = -1;
	while (++y < WIN_H)
	{
		x = -1;
		while (++x < WIN_W)
			(f(GTKMGR.saved + (y * stride) + x * 4));
	}
}

void				end_filters(void)
{
	gtk_widget_set_tooltip_text(FILTER_VIEW.bw_button, "Black & White");
	g_signal_connect(G_OBJECT(FILTER_VIEW.bw_button), "clicked",
	G_CALLBACK(handle_filters), NULL);
	gtk_button_set_image(GTK_BUTTON(FILTER_VIEW.bw_button), FILTER_VIEW.bw_img);
	gtk_container_add(GTK_CONTAINER(FILTER_VIEW.buttonbox),
	FILTER_VIEW.bw_button);
	gtk_container_add(GTK_CONTAINER(FILTER_VIEW.buttonbox),
	FILTER_VIEW.reversed_button);
	FILTER_VIEW.sepia_button = gtk_button_new();
	gtk_widget_set_tooltip_text(FILTER_VIEW.sepia_button, "Sepia");
	gtk_widget_set_tooltip_text(FILTER_VIEW.reversed_button, "Invert Colors");
	g_signal_connect(G_OBJECT(FILTER_VIEW.sepia_button), "clicked",
	G_CALLBACK(handle_filters), NULL);
	g_signal_connect(G_OBJECT(FILTER_VIEW.reversed_button), "clicked",
	G_CALLBACK(handle_filters), NULL);
	gtk_button_set_image(GTK_BUTTON(FILTER_VIEW.sepia_button),
	FILTER_VIEW.sepia_img);
	gtk_container_add(GTK_CONTAINER(FILTER_VIEW.buttonbox),
	FILTER_VIEW.sepia_button);
	gtk_button_set_image(GTK_BUTTON(FILTER_VIEW.reversed_button),
	FILTER_VIEW.reversed_img);
	handle_filter_validation();
}

void				filter_win(void)
{
	GtkWidget		*content_area;

	if (!(GTKMGR.saved = ft_ustrdup(GTKMGR.buf,
	WIN_H * cairo_format_stride_for_width(CAIRO_FORMAT_RGB24, WIN_W))))
		exit_properly(1);
	init_filter_img();
	FILTER_VIEW.win = gtk_dialog_new_with_buttons("Filters",
	GTK_WINDOW(GTKMGR.ui.main_view.win),
	GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, "_OK",
	GTK_RESPONSE_ACCEPT, "_Cancel", GTK_RESPONSE_REJECT, NULL);
	gtk_window_set_transient_for(GTK_WINDOW(FILTER_VIEW.win),
	GTK_WINDOW(GTKMGR.ui.main_view.win));
	gtk_window_set_position(GTK_WINDOW(FILTER_VIEW.win), GTK_WIN_POS_MOUSE);
	content_area = gtk_dialog_get_content_area(GTK_DIALOG(FILTER_VIEW.win));
	FILTER_VIEW.grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(content_area), FILTER_VIEW.grid);
	FILTER_VIEW.buttonbox = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
	gtk_grid_attach(GTK_GRID(FILTER_VIEW.grid), FILTER_VIEW.buttonbox,
	0, 0, 4, 1);
	FILTER_VIEW.bw_button = gtk_button_new();
	FILTER_VIEW.reversed_button = gtk_button_new();
	g_signal_connect(G_OBJECT(FILTER_VIEW.win),
	"key-press-event", G_CALLBACK(on_key_press), NULL);
	end_filters();
}
