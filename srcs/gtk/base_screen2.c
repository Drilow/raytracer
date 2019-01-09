/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_screen2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dagnear <Dagnear@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 17:01:11 by adleau            #+#    #+#             */
/*   Updated: 2019/01/09 12:15:04 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <fcntl.h>
#include <libft.h>
#include <parser/parser.h>
#include <display/display.h>
#define PIXMAP g_global.r->gtk_mgr.pixmap
#define GTKMGR g_global.r->gtk_mgr
#define ADD_VIEW g_global.r->gtk_mgr.ui.add_view
#define PROGRESS_DATA g_global.r->gtk_mgr.ui.progress_data
#define FILTER_VIEW GTKMGR.ui.filter_view

extern t_global				g_global;

void						on_key_press(GtkWidget *w, GdkEventKey *event)
{
	printf("MA COUILLE\n");
	if (event->keyval != GDK_KEY_Escape)
		return ;
	if (w == g_global.base_view.win && event->keyval == GDK_KEY_Escape)
	{
		printf("AHAHAHAHAHAHAH\n");
		gtk_main_quit();
		return ;
	}
	if (event->keyval == GDK_KEY_Escape && w == FILTER_VIEW.win)
	{
		redraw(true);
		gtk_widget_destroy(w);
		return ;
	}
	if (g_global.r && w == ADD_VIEW.win && event->keyval == GDK_KEY_Escape)
	{
		redraw(false);
		return ;
	}
	if (event->keyval == GDK_KEY_Escape &&
	w != NULL && w != PROGRESS_DATA.window)
	{
		if (GTK_IS_WIDGET(w))
		{
			gtk_widget_destroy(GTK_WIDGET(w));
			w = NULL;
		}
	}
}

void						end_open(GtkWidget *dialog)
{
	char					*filename;
	GtkFileChooser			*chooser;
	GtkCssProvider			*css_provider;

	css_provider = gtk_css_provider_new();
	gtk_css_provider_load_from_path(css_provider,
	"./uiconfig/progressbar.css", NULL);
	gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
	GTK_STYLE_PROVIDER(css_provider),
	GTK_STYLE_PROVIDER_PRIORITY_USER);
	chooser = GTK_FILE_CHOOSER(dialog);
	filename = gtk_file_chooser_get_filename(chooser);
	if (!parse(filename))
		usage("Error : invalid argument.", 1);
	g_free(filename);
	if (dialog)
	{
		gtk_widget_destroy(dialog);
		dialog = NULL;
	}
	handle_main_view();
	scene_win();
}

void						dialog_keyhook(GtkWidget *w, GdkEventKey *event)
{
	printf("%d\n", event->keyval);
	if (event->keyval == GDK_KEY_Escape)
	{
		if (w == ADD_VIEW.win)
			redraw(false);
		gtk_widget_destroy(w);
	}
	else if (event->keyval == 65421 || event->keyval == 65293)
		end_open(w);
	else
		return ;
}

void						open_file_append(gint res, GtkWidget *dialog)
{
	if (res == GTK_RESPONSE_ACCEPT)
		end_open(dialog);
	else
	{
		if (GTK_IS_WIDGET(dialog))
			gtk_widget_destroy(dialog);
		dialog = NULL;
	}
}

void						open_file(void)
{
	GtkWidget				*dialog;
	GtkFileChooserAction	action;
	gint					res;
	char					*dir;

	dialog = NULL;
	action = GTK_FILE_CHOOSER_ACTION_OPEN;
	dialog = gtk_file_chooser_dialog_new("Open File",
	GTK_WINDOW(g_global.base_view.win), action, "_Cancel",
	GTK_RESPONSE_CANCEL, "_Open", GTK_RESPONSE_ACCEPT, NULL);
	g_signal_connect(G_OBJECT(dialog), "key-press-event",
					G_CALLBACK(dialog_keyhook), NULL);
	if (!(dir = (char*)malloc(sizeof(char) * PATH_MAX + 1)))
		exit(1); // to fix
	dir = getwd(dir);
	gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog),
	(dir = ft_strjoin(dir, "/scenes")));
	init_rt();
	init_gtk_variables();
	free(dir);
	dir = NULL;
	res = gtk_dialog_run(GTK_DIALOG(dialog));
	open_file_append(res, dialog);
}
