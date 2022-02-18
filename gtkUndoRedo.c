#include <gtk/gtk.h>

void undo_redo(GtkWidget *widget,  gpointer item) 
{
    static gint count = 2;

    /* 得到控件的名字 */
    const gchar *name = gtk_widget_get_name(widget);

    if (g_strcmp0(name, "undo") ) {
      count++;
    } else {
      count--;
    }

    if (count < 0) {
        /* 当count小于0时， redo禁止，undo使能*/
        gtk_widget_set_sensitive(widget, FALSE);
        gtk_widget_set_sensitive(GTK_WIDGET(item), TRUE);
    } 

    if (count > 5) {
        /* 当count大于5时， undo禁止，redo使能*/
        gtk_widget_set_sensitive(widget, FALSE);
        gtk_widget_set_sensitive(GTK_WIDGET(item), TRUE);
    }
}


int main(int argc, char *argv[]) 
{

    GtkWidget *window;
    GtkWidget *vbox;

    GtkWidget *toolbar;
    GtkToolItem *undo;
    GtkToolItem *redo;
    GtkToolItem *sep;
    GtkToolItem *exit;

    gtk_init(&argc, &argv);

    /*创建并设置窗口信息*/
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    gtk_window_set_title(GTK_WINDOW(window), "Undo redo");

    /* 创建布局， 并将布局添加到window中 */
    vbox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);


    toolbar = gtk_toolbar_new();
    gtk_toolbar_set_style(GTK_TOOLBAR(toolbar), GTK_TOOLBAR_ICONS);
    gtk_container_set_border_width(GTK_CONTAINER(toolbar), 2);

    /* 撤销工具图标 */
    undo = gtk_tool_button_new_from_stock(GTK_STOCK_UNDO);
    gtk_widget_set_name(GTK_WIDGET(undo), "undo");
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), undo, -1);

    /* 重做工具图标 */
    redo = gtk_tool_button_new_from_stock(GTK_STOCK_REDO);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), redo, -1);

    /* 添加分割线 */
    sep = gtk_separator_tool_item_new();
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), sep, -1); 

    /* 退出图标 */
    exit = gtk_tool_button_new_from_stock(GTK_STOCK_QUIT);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), exit, -1);

    gtk_box_pack_start(GTK_BOX(vbox), toolbar, FALSE, FALSE, 0);

    /* 设置各选项的事件 */
    g_signal_connect(G_OBJECT(undo), "clicked", 
          G_CALLBACK(undo_redo), redo);

    g_signal_connect(G_OBJECT(redo), "clicked", 
          G_CALLBACK(undo_redo), undo);

    g_signal_connect(G_OBJECT(exit), "clicked", 
          G_CALLBACK(gtk_main_quit), NULL);

    g_signal_connect(G_OBJECT(window), "destroy",
          G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}