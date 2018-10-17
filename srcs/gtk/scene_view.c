#include <global.h>
#include <parser/parser.h>
#include <fcntl.h>
#include <libft.h>
#define PIXMAP g_global.r->gtk_mgr.pixmap
#define GTKMGR g_global.r->gtk_mgr
#define SCENE_VIEW g_global.r->gtk_mgr.ui.scene_view

extern t_global		g_global;

enum
{
   TYPE_COLUMN,
   POS_X_COLUMN,
   POS_Y_COLUMN,
   POS_Z_COLUMN,
   SIZE_COLUMN,
   CHECKED_COLUMN,
   N_COLUMNS
};

static char 			*get_obj_type(int type)
{
	if (type == 1)
		return("Sphère");
	else if (type == 2)
		return("Plane");
	else if (type == 3)
		return("Cone");
	else if (type == 4)
		return("Cylinder");
	else if (type == 6)
		return("Poly");
	else if (type == 66)
		return("Cube");
	else if (type == 67)
		return("Tetra");
	return(NULL);
}

void      init_scene_view(void)
{
  GTKMGR.ui.scene_view.win = NULL;
  GTKMGR.ui.scene_view.button = NULL;
  GTKMGR.ui.scene_view.tree = NULL;
}

void 			read_obj(GtkTreeStore *store, t_obj *obj)
{
	GtkTreeIter iter1;

gtk_tree_store_append (store, &iter1, NULL);
gtk_tree_store_set (store, &iter1,
                    TYPE_COLUMN, get_obj_type(obj->type),
                    POS_X_COLUMN, obj->position.x,
                    POS_Y_COLUMN, obj->position.y,
                    POS_Z_COLUMN, obj->position.z,
                    SIZE_COLUMN, obj->size,
                    CHECKED_COLUMN, TRUE,
                    -1);
}

void 			read_light(GtkTreeStore *store, t_light *light)
{
	GtkTreeIter iter1;

gtk_tree_store_append (store, &iter1, NULL);
gtk_tree_store_set (store, &iter1,
                    TYPE_COLUMN, "Light",
                    POS_X_COLUMN, light->source.x,
                    POS_Y_COLUMN, light->source.y,
                    POS_Z_COLUMN, light->source.z,
                    SIZE_COLUMN, (double)0,
                    CHECKED_COLUMN, TRUE,
                    -1);
}

void 			populate_tree_model(GtkTreeStore *store)
{
	GtkTreeIter iter1;
	t_obj		*tmp_objs;
	t_light     *tmp_lights;

	tmp_objs = g_global.r->objects;
	tmp_lights = g_global.r->lights;
	while (tmp_objs != NULL)
	{
		read_obj(store, tmp_objs);
		tmp_objs = tmp_objs->next;
	}
	while (tmp_lights != NULL)
	{
		read_light(store, tmp_lights);
		tmp_lights = tmp_lights->next;
	}
	gtk_tree_store_append (store, &iter1, NULL);
	gtk_tree_store_set (store, &iter1,
					TYPE_COLUMN, "Camera",
                    POS_X_COLUMN, g_global.r->cam_position.x,
                    POS_Y_COLUMN, g_global.r->cam_position.y,
                    POS_Z_COLUMN, g_global.r->cam_position.z,
                    SIZE_COLUMN, (double)0,
                    CHECKED_COLUMN, TRUE,
                    -1);
}

void 				append_column_with_text(GtkWidget *tree, char *text, GtkCellRenderer *renderer, int en_column)
{
	GtkTreeViewColumn *column;
	column = gtk_tree_view_column_new_with_attributes (text, renderer,
                                                      "text", en_column,
                                                      NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (tree), column);
}

/*static void checked_row(GtkCellRendererToggle *cell,
               gchar *path_str,
               gpointer data)
{
        // get the treemodel from somewhere
        GtkTreeIter  iter;
        GtkTreePath *path = gtk_tree_path_new_from_string (path_str);
        gboolean enabled;

        gtk_tree_model_get_iter (GTK_TREE_MODEL(SCENE_VIEW.tree), &iter, path);
        gtk_tree_model_get (GTK_TREE_MODEL(SCENE_VIEW.tree), &iter, CHECKED_COLUMN, &enabled, -1);
        enabled ^= 1;

  // do something with the new enabled value, and set the new
  // enabled value in your treemodel
        printf("jambon");

        gtk_tree_path_free (path);
}*/

void				scene_win(void)
{
	GtkTreeStore *store;
	GtkTreeViewColumn *column;
	GtkCellRenderer *renderer;

	init_scene_view();
	SCENE_VIEW.win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW(SCENE_VIEW.win), "Scene");
	gtk_window_set_transient_for(GTK_WINDOW(SCENE_VIEW.win), GTK_WINDOW(GTKMGR.ui.main_view.win));
	gtk_window_set_position(GTK_WINDOW(SCENE_VIEW.win), GTK_WIN_POS_MOUSE);

   store = gtk_tree_store_new (N_COLUMNS,
                               G_TYPE_STRING,
                               G_TYPE_DOUBLE,
                               G_TYPE_DOUBLE,
                               G_TYPE_DOUBLE,
                               G_TYPE_DOUBLE,
                               G_TYPE_BOOLEAN,
                               -1);

   populate_tree_model (store);
   SCENE_VIEW.tree = gtk_tree_view_new_with_model (GTK_TREE_MODEL (store));
   g_object_unref (G_OBJECT (store));

   renderer = gtk_cell_renderer_text_new ();
   g_object_set (G_OBJECT (renderer),
                 "foreground", "red",
                 NULL);
   append_column_with_text(SCENE_VIEW.tree, "Type", renderer, TYPE_COLUMN);
	renderer = gtk_cell_renderer_text_new ();
   	g_object_set(renderer,
               "weight", PANGO_WEIGHT_BOLD,
               "weight-set", TRUE,
               NULL);
   	append_column_with_text(SCENE_VIEW.tree, "Pos X", renderer, POS_X_COLUMN);
   	append_column_with_text(SCENE_VIEW.tree, "Pos Y", renderer, POS_Y_COLUMN);
   	append_column_with_text(SCENE_VIEW.tree, "Pos Z", renderer, POS_Z_COLUMN);
   renderer = gtk_cell_renderer_text_new ();
   g_object_set (G_OBJECT (renderer),
                 "foreground", "blue",
                 NULL);
   append_column_with_text(SCENE_VIEW.tree, "Size", renderer, SIZE_COLUMN);
   renderer = gtk_cell_renderer_toggle_new ();
   //g_signal_connect (G_OBJECT(renderer), "toggled", G_CALLBACK
    //                                                  (checked_row), NULL);
   column = gtk_tree_view_column_new_with_attributes ("Checked out",
                                                      renderer,
                                                      "active", CHECKED_COLUMN,
                                                      NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (SCENE_VIEW.tree), column);

	gtk_container_add(GTK_CONTAINER(SCENE_VIEW.win), SCENE_VIEW.tree);
    gtk_widget_show_all(SCENE_VIEW.win);
	return;
}