// #include <gtk/gtk.h>

// // Callback function for button click event
// static void on_button_clicked(GtkWidget *widget, gpointer data) {
//     GtkWidget *dialog;
//     dialog = gtk_message_dialog_new(GTK_WINDOW(data),
//                                     GTK_DIALOG_MODAL,
//                                     GTK_MESSAGE_INFO,
//                                     GTK_BUTTONS_OK,
//                                     "Button clicked!");
//     gtk_dialog_run(GTK_DIALOG(dialog));
//     gtk_widget_destroy(dialog);
// }

// int main(int argc, char *argv[]) {
//     GtkWidget *window;
//     GtkWidget *button;

//     gtk_init(&argc, &argv);

//     // Create a new window
//     window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
//     gtk_window_set_title(GTK_WINDOW(window), "Basic GTK UI");
//     gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

//     // Connect the window's destroy signal to the GTK main loop
//     g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

//     // Create a button
//     button = gtk_button_new_with_label("Click Me");

//     // Connect the button's clicked signal to the callback function
//     g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), window);

//     // Add the button to the window
//     gtk_container_add(GTK_CONTAINER(window), button);

//     // Show all widgets
//     gtk_widget_show_all(window);

//     // Start the GTK main loop
//     gtk_main();

//     return 0;
// }


#include <array>
#include <iostream>

int main() {

    std::array<int , 10>a;
    std::cout<<a.size()<<std::endl;
    return 0;
}
