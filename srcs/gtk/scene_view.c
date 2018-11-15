/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_view.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dagnear <Dagnear@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 12:54:02 by adleau            #+#    #+#             */
/*   Updated: 2018/11/15 19:34:36 by Dagnear          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <parser/parser.h>
#include <objects/object.h>
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
   CHECKED_COLUMN,
   CHECKED_ACTIVE,
   OBJ_REF,
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

void 			read_obj(t_obj *obj)
{
	GtkTreeIter iter1;

gtk_tree_store_append (SCENE_VIEW.store, &iter1, NULL);
gtk_tree_store_set (SCENE_VIEW.store, &iter1,
                    TYPE_COLUMN, get_obj_type(obj->type),
                    POS_X_COLUMN, obj->position.x,
                    POS_Y_COLUMN, obj->position.y,
                    POS_Z_COLUMN, obj->position.z,
                    CHECKED_COLUMN, TRUE,
                    CHECKED_ACTIVE, TRUE,
                    OBJ_REF, (gpointer)obj,
                    -1);
}

void 			read_light(t_light *light)
{
	GtkTreeIter iter1;

gtk_tree_store_append (SCENE_VIEW.store, &iter1, NULL);
gtk_tree_store_set (SCENE_VIEW.store, &iter1,
                    TYPE_COLUMN, "Light",
                    POS_X_COLUMN, light->source.x,
                    POS_Y_COLUMN, light->source.y,
                    POS_Z_COLUMN, light->source.z,
                    CHECKED_COLUMN, TRUE,
                    CHECKED_ACTIVE, TRUE,
                    OBJ_REF, (gpointer)light,
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
		read_obj(tmp_objs);
		tmp_objs = tmp_objs->next;
	}
	while (tmp_lights != NULL)
	{
		read_light(tmp_lights);
		tmp_lights = tmp_lights->next;
	}
	gtk_tree_store_append (store, &iter1, NULL);
	gtk_tree_store_set (store, &iter1, TYPE_COLUMN, "Camera",
                    POS_X_COLUMN, g_global.r->cam_position.x,
                    POS_Y_COLUMN, g_global.r->cam_position.y,
                    POS_Z_COLUMN, g_global.r->cam_position.z,
                    CHECKED_COLUMN, TRUE,
                    CHECKED_ACTIVE, FALSE,
                    OBJ_REF, (gpointer)&g_global.r->cam_position, -1);
}

void 				append_column_with_text(GtkWidget *tree, char *text, GtkCellRenderer *renderer, int en_column)
{
	GtkTreeViewColumn *column;
	column = gtk_tree_view_column_new_with_attributes (text, renderer,
                                                      "text", en_column,
                                                      NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (tree), column);
}


bool		go_throu_lights(t_light *curr)
{
	t_light	*tmp;

	tmp = g_global.r->lights;
	while (tmp)
	{
		if (curr == tmp)
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

static void checked_row(__attribute__((unused))GtkCellRendererToggle *cell,
						gchar __attribute__((unused))*path_str,
						__attribute__((unused))gpointer data)
{
	GtkTreeIter  iter;
	GtkTreePath *path = gtk_tree_path_new_from_string (path_str);
	gboolean enabled;
	GtkTreeModel *model;
	gpointer		*obj;

	obj = NULL;
	model = NULL;
	if ((model = gtk_tree_view_get_model (GTK_TREE_VIEW (SCENE_VIEW.tree))) == NULL)
        return ;
	gtk_tree_model_get_iter (model, &iter, path);
	gtk_tree_model_get (model, &iter, CHECKED_COLUMN, &enabled, -1);
	enabled = !enabled;
	gtk_tree_store_set(SCENE_VIEW.store, &iter, CHECKED_COLUMN, enabled, -1);
	if (gtk_tree_model_get_iter(model, &iter, path))
    {
		gtk_tree_model_get (model, &iter, OBJ_REF, &obj, -1);
		if (((t_obj*)obj)->type == 1
			|| ((t_obj*)obj)->type == 1 || ((t_obj*)obj)->type == 2 || ((t_obj*)obj)->type == 3 || ((t_obj*)obj)->type == 4 ||
			((t_obj*)obj)->type == 6 || ((t_obj*)obj)->type == 66 || ((t_obj*)obj)->type == 67)
		{
			((t_obj*)obj)->enabled = enabled;
			printf("WOLOLA %p\n", ((t_obj*)obj)->obj);
		}
		else
		{
			if (go_throu_lights(((t_light*)obj)))
				((t_light*)obj)->enabled = enabled; // a debug
			printf("WOLOLO\n");
		}
	}
	redraw(true);
	gtk_tree_path_free (path);
}

void        select_handler(GtkTreeView *tree_view, GtkTreePath *path,
						   __attribute__((unused))GtkTreeViewColumn *column, __attribute__((unused))gpointer user_data)
{
	gpointer *obj;
	GtkTreeModel *model;
	GtkTreeIter iter;

	model = NULL;
	if ((model = gtk_tree_view_get_model (tree_view)) == NULL)
		return ;
	if (gtk_tree_model_get_iter(model, &iter, path))
    {
		gtk_tree_model_get (model, &iter, OBJ_REF, &obj, -1);
		printf("objet select : %d\n", ((t_obj*)obj)->type);
		if (((t_obj*)obj)->type != 0)
		{
            outline_obj(((t_obj*)obj));
            edit_win(((t_obj*)obj));
		}
		g_print ("You selected obj %i\n", ((t_obj*)obj)->type);
    }
}

void				scene_win(void)
{

	GtkTreeViewColumn *column;
	GtkCellRenderer *renderer;

	init_scene_view();
	SCENE_VIEW.win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW(SCENE_VIEW.win), "Scene");
	gtk_window_set_transient_for(GTK_WINDOW(SCENE_VIEW.win), GTK_WINDOW(GTKMGR.ui.main_view.win));
	gtk_window_set_position(GTK_WINDOW(SCENE_VIEW.win), GTK_WIN_POS_MOUSE);

   SCENE_VIEW.store = gtk_tree_store_new (N_COLUMNS,
                               G_TYPE_STRING,
                               G_TYPE_DOUBLE,
                               G_TYPE_DOUBLE,
                               G_TYPE_DOUBLE,
                               G_TYPE_BOOLEAN,
                               G_TYPE_BOOLEAN,
                               G_TYPE_POINTER,
                               -1);

   populate_tree_model (SCENE_VIEW.store);
   SCENE_VIEW.tree = gtk_tree_view_new_with_model (GTK_TREE_MODEL (SCENE_VIEW.store));
   g_object_unref (G_OBJECT (SCENE_VIEW.store));

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
   renderer = gtk_cell_renderer_toggle_new ();
   gtk_cell_renderer_toggle_set_activatable(GTK_CELL_RENDERER_TOGGLE(renderer), TRUE);
   g_signal_connect (G_OBJECT(renderer), "toggled", G_CALLBACK
                                                      (checked_row), NULL);
   column = gtk_tree_view_column_new_with_attributes ("Visible",
                                                      renderer,
                                                      "active", CHECKED_COLUMN,
                                                      NULL);
   gtk_tree_view_column_add_attribute (column, renderer, "activatable", CHECKED_ACTIVE);
	gtk_tree_view_append_column(GTK_TREE_VIEW(SCENE_VIEW.tree), column);

  g_signal_connect(G_OBJECT(SCENE_VIEW.tree), "row-activated",
    G_CALLBACK(select_handler), NULL);
	gtk_container_add(GTK_CONTAINER(SCENE_VIEW.win), SCENE_VIEW.tree);
    gtk_widget_show_all(SCENE_VIEW.win);
	return;
}
