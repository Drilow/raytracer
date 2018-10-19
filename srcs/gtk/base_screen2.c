/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_screen2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dagnear <Dagnear@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 17:01:11 by adleau            #+#    #+#             */
/*   Updated: 2018/10/19 20:30:45 by Dagnear          ###   ########.fr       */
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

extern t_global		g_global;

/* Update the value of the progress bar so that we get
 * some movement */
void UpdateProgress (long pos, long len)
{
    gfloat pvalue;
    int pct;

    /* --- Prevent divide by zero errors --- */
    if (len > 0) {

        /* --- Calculate the percentage --- */
        pvalue = (gfloat) pos / (gfloat) len;

        pct = pvalue * 100;

        if (PROGRESS_DATA.nLastPct != pct) {
			gtk_progress_bar_pulse (GTK_PROGRESS_BAR (PROGRESS_DATA.pbar));
            /* --- Update the displayed value --- */
            gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (PROGRESS_DATA.pbar),
                               1 / len);
            gtk_progress_bar_set_text(GTK_PROGRESS_BAR(PROGRESS_DATA.pbar), ft_itoa(pct));
            /* --- Repaint any windows - like the progress bar --- */
            while (gtk_events_pending ()) {
                gtk_main_iteration ();
            }
            PROGRESS_DATA.nLastPct = pct;
        }
    }
}

// void EndProgress ()
// {
//     /* --- Allow it to close --- */
//     PROGRESS_DATA.bProgressUp = FALSE;

//     /* --- Destroy the window --- */
//     gtk_widget_destroy (PROGRESS_DATA.window);
// }

void			progress_bar()
{
    //GtkWidget *button;

    //PROGRESS_DATA = g_malloc (sizeof (t_progress_data));
    PROGRESS_DATA.nLastPct = -1;
    PROGRESS_DATA.bProgressUp = TRUE;
    PROGRESS_DATA.pbar = NULL;
    PROGRESS_DATA.window = NULL;

    PROGRESS_DATA.window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (PROGRESS_DATA.window), "Loading");
    //gtk_window_set_transient_for(GTK_WINDOW(PROGRESS_DATA.window), GTK_WINDOW(GTKMGR.ui.main_view.win));
	gtk_window_set_position(GTK_WINDOW(PROGRESS_DATA.window), GTK_WIN_POS_MOUSE);

    /* Create the GtkProgressBar */
    PROGRESS_DATA.pbar = gtk_progress_bar_new ();
    gtk_container_add (GTK_CONTAINER(PROGRESS_DATA.window), PROGRESS_DATA.pbar);
    gtk_widget_show_all(PROGRESS_DATA.window);

    return ;
}

void			on_key_press(GtkWidget *w, GdkEventKey *event)
{
	if (event->keyval == GDK_KEY_Escape)
		gtk_widget_destroy(w);
	else if (event->keyval != GDK_KEY_Escape)
		return ;
	if (g_global.r && w == ADD_VIEW.win)
		draw_image();
	if (w == g_global.base_view.win && event->keyval == GDK_KEY_Escape)
		gtk_main_quit();
}

void			dialog_keyhook(GtkWidget *w, GdkEventKey *event)
{
	if (event->keyval == GDK_KEY_Escape)
	{
		if (w == ADD_VIEW.win)
			redraw(false);
		gtk_widget_destroy(w);
	}
	else
		return ;
}

void			end_open(GtkWidget *dialog)
{
	char					*filename;
	GtkFileChooser			*chooser;

	chooser = GTK_FILE_CHOOSER(dialog);
	filename = gtk_file_chooser_get_filename(chooser);
	if (!parse(filename))
		usage("Error : invalid argument.", 1);
	g_free(filename);
	handle_main_view();
}

void			open_file(void)
{
	GtkWidget				*dialog;
	GtkFileChooserAction	action;
	gint					res;
	char					*dir;

	action = GTK_FILE_CHOOSER_ACTION_OPEN;
	dialog = gtk_file_chooser_dialog_new("Open File",
	GTK_WINDOW(g_global.base_view.win), action, "_Cancel",
	GTK_RESPONSE_CANCEL, "_Open", GTK_RESPONSE_ACCEPT, NULL);
	if (!(dir = (char*)malloc(sizeof(char) * PATH_MAX + 1)))
		exit(1);
	dir = getwd(dir);
	gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog),
	(dir = ft_strjoin(dir, "/scenes")));
	init_rt();
	init_gtk_variables();
	free(dir);
	dir = NULL;
	g_signal_connect(G_OBJECT(dialog), "key-press-event",
	G_CALLBACK(dialog_keyhook), NULL);
	res = gtk_dialog_run(GTK_DIALOG(dialog));
	if (res == GTK_RESPONSE_ACCEPT)
		end_open(dialog);
	else
		g_object_unref(dialog);
}
