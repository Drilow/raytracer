/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_screen2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dagnear <Dagnear@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 17:01:11 by adleau            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2018/10/22 12:22:39 by Dagnear          ###   ########.fr       */
=======
/*   Updated: 2018/10/20 11:47:50 by adleau           ###   ########.fr       */
>>>>>>> 99c9d7ab43d8b2b0a01a1df3b5095e745df703aa
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
gboolean updateProgress (gpointer user_data)
{
    gfloat pvalue;
    t_point *pos = user_data;
    gdouble fraction;
    int pct;

    ft_putendl("jambon1");
    /* --- Prevent divide by zero errors --- */
    if (WIN_W > 0) {
ft_putendl("jambon2");
        /* --- Calculate the percentage --- */
        pvalue = (gfloat) pos->x / (gfloat) WIN_W;

        pct = pvalue * 100;

        if (PROGRESS_DATA.nLastPct != pct)
        {
        	printf("pos = %d len = %d pos/len = %f\nnlastpct = %d\n", pos->x, WIN_W, pvalue, PROGRESS_DATA.nLastPct);
			gtk_progress_bar_pulse (GTK_PROGRESS_BAR (PROGRESS_DATA.pbar));
            /* --- Update the displayed value --- */
            fraction = gtk_progress_bar_get_fraction (GTK_PROGRESS_BAR (PROGRESS_DATA.pbar));
            fraction = pct;
            gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (PROGRESS_DATA.pbar),
                               fraction);
            gtk_progress_bar_set_text(GTK_PROGRESS_BAR(PROGRESS_DATA.pbar), ft_itoa(pct));
            /* --- Repaint any windows - like the progress bar --- */
            //while (gtk_events_pending ()) {
             //   gtk_main_iteration ();
            //}
            PROGRESS_DATA.nLastPct = pct;
        }
    }
    return (TRUE);
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
    gtk_window_set_transient_for(GTK_WINDOW(PROGRESS_DATA.window), GTK_WINDOW(GTKMGR.ui.main_view.win));
	gtk_window_set_position(GTK_WINDOW(PROGRESS_DATA.window), GTK_WIN_POS_MOUSE);
	gtk_window_set_default_size (GTK_WINDOW (PROGRESS_DATA.window), 220, 20);

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


void			end_open(GtkWidget *dialog)
{
	char					*filename;
	GtkFileChooser			*chooser;

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
}

void			dialog_keyhook(GtkWidget *w, GdkEventKey *event)
{
	if (event->keyval == GDK_KEY_Escape)
	{
		if (w == ADD_VIEW.win)
			redraw(false);
		gtk_widget_destroy(w);
	}
	else if (event->keyval == 65421)
		end_open(w);
}

void			open_file(void)
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
	g_signal_connect(G_OBJECT(dialog), "key-press-event",
	G_CALLBACK(dialog_keyhook), NULL);
	if (res == GTK_RESPONSE_ACCEPT)
		end_open(dialog);
	else
	{
		if (dialog)
			gtk_widget_destroy(dialog);
		dialog = NULL;
	}
}
