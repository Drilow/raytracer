/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_view.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 07:36:43 by adleau            #+#    #+#             */
/*   Updated: 2019/02/06 15:28:16 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>

extern t_global		g_global;

void				handle_filter_validation(void)
{
	int		r;

	gtk_widget_show_all(g_global.r.gtk_mgr.ui.filter_view.win);
	r = gtk_dialog_run(GTK_DIALOG(g_global.r.gtk_mgr.ui.filter_view.win));
	if (r == GTK_RESPONSE_ACCEPT)
	{
		gtk_widget_destroy(g_global.r.gtk_mgr.ui.filter_view.win);
		redraw(false);
	}
	else if (r == GTK_RESPONSE_REJECT)
	{
		free(g_global.r.gtk_mgr.buf);
		g_global.r.gtk_mgr.buf = NULL;
		g_global.r.gtk_mgr.buf = ft_ustrdup(g_global.r.gtk_mgr.saved,
		WIN_H * cairo_format_stride_for_width(CAIRO_FORMAT_RGB24, WIN_W));
		gtk_widget_destroy(g_global.r.gtk_mgr.ui.filter_view.win);
		redraw(true);
	}
}

void				deactivate_filter_buttons(GtkWidget *except)
{
	if (&(g_global.r.gtk_mgr.ui.filter_view.bw_button) != &except)
		gtk_widget_set_state_flags(g_global.r.gtk_mgr.ui.filter_view.bw_button,
		GTK_STATE_FLAG_NORMAL, true);
	if (&(g_global.r.gtk_mgr.ui.filter_view.sepia_button) != &except)
		gtk_widget_set_state_flags(
		g_global.r.gtk_mgr.ui.filter_view.sepia_button,
		GTK_STATE_FLAG_NORMAL, true);
	if (&(g_global.r.gtk_mgr.ui.filter_view.reversed_button) != &except)
		gtk_widget_set_state_flags(
		g_global.r.gtk_mgr.ui.filter_view.reversed_button,
		GTK_STATE_FLAG_NORMAL, true);
}

void				handle_filters(GtkButton *button)
{
	int				x;
	int				y;
	int				stride;
	void			(*f)(unsigned char*);

	if (button == GTK_BUTTON(g_global.r.gtk_mgr.ui.filter_view.bw_button))
		f = black_white;
	else if (button == GTK_BUTTON(
	g_global.r.gtk_mgr.ui.filter_view.sepia_button))
		f = sepia;
	else if (button == GTK_BUTTON(
	g_global.r.gtk_mgr.ui.filter_view.reversed_button))
		f = reversed;
	deactivate_filter_buttons((GtkWidget*)button);
	stride = cairo_format_stride_for_width(CAIRO_FORMAT_RGB24, WIN_W);
	y = -1;
	while (++y < WIN_H)
	{
		x = -1;
		while (++x < WIN_W)
			(f(g_global.r.gtk_mgr.saved + (y * stride) + x * 4));
	}
}

void				end_filters(void)
{
	gtk_widget_set_tooltip_text(g_global.r.gtk_mgr.ui.filter_view.bw_button,
	"Black & White");
	g_signal_connect(G_OBJECT(g_global.r.gtk_mgr.ui.filter_view.bw_button),
	"clicked", G_CALLBACK(handle_filters), NULL);
	gtk_button_set_image(GTK_BUTTON(
	g_global.r.gtk_mgr.ui.filter_view.bw_button),
	g_global.r.gtk_mgr.ui.filter_view.bw_img);
	gtk_container_add(GTK_CONTAINER(
	g_global.r.gtk_mgr.ui.filter_view.buttonbox),
	g_global.r.gtk_mgr.ui.filter_view.bw_button);
	gtk_container_add(GTK_CONTAINER(
	g_global.r.gtk_mgr.ui.filter_view.buttonbox),
	g_global.r.gtk_mgr.ui.filter_view.reversed_button);
	g_global.r.gtk_mgr.ui.filter_view.sepia_button = gtk_button_new();
	gtk_widget_set_tooltip_text(g_global.r.gtk_mgr.ui.filter_view.sepia_button,
	"Sepia");
	gtk_widget_set_tooltip_text(
	g_global.r.gtk_mgr.ui.filter_view.reversed_button, "Invert Colors");
	g_signal_connect(G_OBJECT(g_global.r.gtk_mgr.ui.filter_view.sepia_button),
	"clicked", G_CALLBACK(handle_filters), NULL);
	g_signal_connect(G_OBJECT(g_global.r.gtk_mgr.ui.filter_view.reversed_button)
	, "clicked", G_CALLBACK(handle_filters), NULL);
	gtk_button_set_image(GTK_BUTTON(
	g_global.r.gtk_mgr.ui.filter_view.sepia_button),
	g_global.r.gtk_mgr.ui.filter_view.sepia_img);
	gtk_container_add(GTK_CONTAINER(
	g_global.r.gtk_mgr.ui.filter_view.buttonbox),
	g_global.r.gtk_mgr.ui.filter_view.sepia_button);
	gtk_button_set_image(GTK_BUTTON(
	g_global.r.gtk_mgr.ui.filter_view.reversed_button),
	g_global.r.gtk_mgr.ui.filter_view.reversed_img);
	handle_filter_validation();
}

void				filter_win(void)
{
	GtkWidget		*content_area;

	if (!g_global.r.gtk_mgr.saved)
		if (!(g_global.r.gtk_mgr.saved = ft_ustrdup(g_global.r.gtk_mgr.buf,
		WIN_H * cairo_format_stride_for_width(CAIRO_FORMAT_RGB24, WIN_W))))
			exit_properly(1);
	init_filter_img();
	g_global.r.gtk_mgr.ui.filter_view.win = gtk_dialog_new_with_buttons(
	"Filters", GTK_WINDOW(g_global.r.gtk_mgr.ui.main_view.win),
	GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, "_OK",
	GTK_RESPONSE_ACCEPT, "_Cancel", GTK_RESPONSE_REJECT, NULL);
	gtk_window_set_transient_for(GTK_WINDOW(
	g_global.r.gtk_mgr.ui.filter_view.win),
	GTK_WINDOW(g_global.r.gtk_mgr.ui.main_view.win));
	gtk_window_set_position(GTK_WINDOW(
	g_global.r.gtk_mgr.ui.filter_view.win), GTK_WIN_POS_MOUSE);
	content_area = gtk_dialog_get_content_area(
	GTK_DIALOG(g_global.r.gtk_mgr.ui.filter_view.win));
	g_global.r.gtk_mgr.ui.filter_view.grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(content_area),
	g_global.r.gtk_mgr.ui.filter_view.grid);
	g_global.r.gtk_mgr.ui.filter_view.buttonbox = gtk_button_box_new(
	GTK_ORIENTATION_HORIZONTAL);
	gtk_grid_attach(GTK_GRID(g_global.r.gtk_mgr.ui.filter_view.grid),
	g_global.r.gtk_mgr.ui.filter_view.buttonbox, 0, 0, 4, 1);
	g_global.r.gtk_mgr.ui.filter_view.bw_button = gtk_button_new();
	g_global.r.gtk_mgr.ui.filter_view.reversed_button = gtk_button_new();
	g_signal_connect(G_OBJECT(g_global.r.gtk_mgr.ui.filter_view.win),
	"key-press-event", G_CALLBACK(on_key_press), NULL);
	end_filters();
}
