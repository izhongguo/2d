#include <cairo.h>
#include <gtk/gtk.h>

static gboolean
on_expose_event (GtkWidget * widget,
                 GdkEventExpose * event, gpointer data)
{
        cairo_t *cr;

        cr = gdk_cairo_create (widget->window);

        /* 设置画笔颜色 */
        cairo_set_source_rgba (cr, 0, 0, 0,1);
        static const double dashed1[] ={4.0,1.0 };
        static int len1 =sizeof(dashed1) /sizeof(dashed1[0]);

        static const double dashed2[] ={4.0,10.0, 4.0 };
        static int len2 =sizeof(dashed2) /sizeof(dashed2[0]);

        static const double dashed3[] ={1.0};
        /* 设置线宽 */
        cairo_set_line_width (cr, 1.5);
        /* 设置虚线样式 */
        cairo_set_dash (cr, dashed1, len1, 0);

        cairo_move_to (cr, 40, 60);
        cairo_line_to (cr, 360, 60);
        //将绘制信息画在屏幕上，并清除信息
        cairo_stroke (cr);

        cairo_set_dash (cr, dashed2, len2, 10);

        cairo_move_to (cr, 40, 120);
        cairo_line_to (cr, 360, 120);
        cairo_stroke (cr);

        cairo_set_dash (cr, dashed3, 1, 0);

        cairo_move_to (cr, 40, 180);
        cairo_line_to (cr, 360, 180);
        cairo_stroke (cr);

        cairo_destroy (cr);

        return FALSE;
}


int
main (int argc,char *argv[])
{

        GtkWidget *window;
        GtkWidget *darea;

        gtk_init (&argc, &argv);

        window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

        darea = gtk_drawing_area_new ();
        gtk_container_add (GTK_CONTAINER (window), darea);

        g_signal_connect (darea, "expose-event",
                          G_CALLBACK (on_expose_event),NULL);
        g_signal_connect (window, "destroy",
                          G_CALLBACK (gtk_main_quit),NULL);

        /* 设置窗口在屏幕正中间 */
        gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
        /* 设置窗口大小 */
        gtk_window_set_default_size (GTK_WINDOW(window),400,300);

        gtk_widget_show_all (window);

        gtk_main ();

        return 0;
}