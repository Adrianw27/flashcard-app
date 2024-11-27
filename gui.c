/*
 * gui.c
 * Author: Angad Chhabra
 * Description: Handles GUI design and interface for the cocoNut Flashcards app.
 */

#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include "user_input.h"
#include "storage.h"
#include "quiz_logic.h"




// Implementing the setup_gui function
void setup_gui(GtkApplication *app) {
    GtkWidget *window = create_main_window(app);
    gtk_widget_show(window);
}

// Function to create the main window and set up the GUI components
static GtkWidget *create_main_window(GtkApplication *app) {
    // Create the main window
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "cocoNut - Flashcard App");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);

    // Create a vertical box to hold all widgets
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_window_set_child(GTK_WINDOW(window), vbox);

    // --- Add Category Section ---
    GtkWidget *add_category_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_append(GTK_BOX(vbox), add_category_box);

    GtkWidget *category_name_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(category_name_entry), "Category Name");
    gtk_box_append(GTK_BOX(add_category_box), category_name_entry);

    GtkWidget *add_category_button = gtk_button_new_with_label("Add Category");
    gtk_box_append(GTK_BOX(add_category_box), add_category_button);
    g_signal_connect(add_category_button, "clicked", G_CALLBACK(on_add_category), category_name_entry);

    // --- Add Flashcard Section ---
    GtkWidget *add_flashcard_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_append(GTK_BOX(vbox), add_flashcard_box);

    GtkWidget *flashcard_category_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(flashcard_category_entry), "Category");
    gtk_box_append(GTK_BOX(add_flashcard_box), flashcard_category_entry);

    GtkWidget *question_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(question_entry), "Question");
    gtk_box_append(GTK_BOX(add_flashcard_box), question_entry);

    GtkWidget *answer_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(answer_entry), "Answer");
    gtk_box_append(GTK_BOX(add_flashcard_box), answer_entry);

    GtkWidget *add_flashcard_button = gtk_button_new_with_label("Add Flashcard");
    gtk_box_append(GTK_BOX(add_flashcard_box), add_flashcard_button);

    // Store the entries in an array
    GtkWidget **flashcard_entries = g_new(GtkWidget *, 3);
    flashcard_entries[0] = flashcard_category_entry;
    flashcard_entries[1] = question_entry;
    flashcard_entries[2] = answer_entry;

    g_signal_connect(add_flashcard_button, "clicked", G_CALLBACK(on_add_flashcard), flashcard_entries);

    // --- Quiz Section ---
    GtkWidget *quiz_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_append(GTK_BOX(vbox), quiz_box);

    GtkWidget *quiz_category_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(quiz_category_entry), "Category");
    gtk_box_append(GTK_BOX(quiz_box), quiz_category_entry);

    GtkWidget *quiz_button = gtk_button_new_with_label("Start Quiz");
    gtk_box_append(GTK_BOX(quiz_box), quiz_button);
    g_signal_connect(quiz_button, "clicked", G_CALLBACK(on_quiz), quiz_category_entry);

    return window;
}
