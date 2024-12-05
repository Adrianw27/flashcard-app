// quiz_logic.c

/*
 * Quiz Logic Implementation
 * -------------------------
 * This file contains the logic for managing quizzes, including:
 * - Comparing user answers to correct answers
 * - Displaying visual feedback for correct answers
 * - Converting strings to lowercase for case-insensitive comparison
 *
 * Dependencies:
 * - quiz_logic.h: Interface for quiz-related functions
 * - storage.h: Provides category and flashcard data
 * - GTK and GLib: For graphical feedback
 */

#include "quiz_logic.h"
#include "storage.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <glib.h>

/*
 * Function: to_lowercase
 * ----------------------
 * Converts a given string to lowercase.
 *
 * Parameters:
 * - input: The input string to convert.
 * - output: The output buffer where the lowercase string is stored.
 *
 * Returns: None
 */
void to_lowercase(char input[], char output[]) {
    int i = 0;
    while (input[i] != '\0') {
        output[i] = tolower((unsigned char)input[i]);
        i++;
    }
    output[i] = '\0';  // Null-terminate the output string
}

/*
 * Function: on_activate
 * ---------------------
 * Callback function for GTK application activation. Displays an image
 * to indicate a correct answer.
 *
 * Parameters:
 * - app: The GTK application instance.
 * - user_data: Pointer to additional user data (unused here).
 *
 * Returns: None
 */
void on_activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *image;

    // Create and configure the GTK window
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Correct Answer!");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    // Load and set the image
    image = gtk_image_new_from_file("happy.png");

    if (image == NULL) {
        g_printerr("Error: Unable to load image 'happy.png'.\n");
        g_application_quit(G_APPLICATION(app));
        return;
    }

    gtk_window_set_child(GTK_WINDOW(window), image);

    // Display the window
    gtk_window_present(GTK_WINDOW(window));
}

/*
 * Function: show_happy_image
 * --------------------------
 * Creates and runs a GTK application to show a "happy" image when the user
 * answers correctly.
 *
 * Parameters: None
 * Returns: None
 */
void show_happy_image() {
    // Create a new GTK application
    GtkApplication *app = gtk_application_new("com.example.GtkApp", G_APPLICATION_FLAGS_NONE);

    // Connect the activation signal to the on_activate callback
    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);

    // Run the application
    g_application_run(G_APPLICATION(app), 0, NULL);

    // Clean up the application object
    g_object_unref(app);
}

/*
 * Function: start_quiz
 * --------------------
 * Starts a quiz for the given category. The user is prompted with each question,
 * and their answers are compared with the correct answers. Visual feedback is provided
 * for correct answers.
 *
 * Parameters:
 * - category_name: The name of the category for the quiz.
 *
 * Returns: None
 */
void start_quiz(char category_name[]) {
    int category_index = find_category_index(category_name);
    if (category_index == -1) {
        printf("Category '%s' not found.\n", category_name);
        return;
    }
    if (flashcard_counts[category_index] == 0) {
        printf("No flashcards in category '%s'.\n", category_name);
        return;
    }

    int total_questions = flashcard_counts[category_index];
    int correct_answers = 0;

    // Loop through all questions in the category
    for (int i = 0; i < total_questions; i++) {
        char question[MAX_QUESTION_LENGTH];
        char correct_answer[MAX_ANSWER_LENGTH];

        strcpy(question, flashcard_questions[category_index][i]);
        strcpy(correct_answer, flashcard_answers[category_index][i]);

        printf("\nQuestion %d: %s\n", i + 1, question);

        char user_answer[MAX_ANSWER_LENGTH];
        printf("Your Answer: ");
        if (fgets(user_answer, MAX_ANSWER_LENGTH, stdin) == NULL) {
            printf("Error reading input.\n");
            continue;
        }
        user_answer[strcspn(user_answer, "\n")] = '\0';

        // Convert answers to lowercase for case-insensitive comparison
        char user_answer_lower[MAX_ANSWER_LENGTH];
        char correct_answer_lower[MAX_ANSWER_LENGTH];
        to_lowercase(user_answer, user_answer_lower);
        to_lowercase(correct_answer, correct_answer_lower);

        if (strcmp(user_answer_lower, correct_answer_lower) == 0) {
            printf("Correct!\n");
            correct_answers++;

            // Show happy image for correct answer
            show_happy_image();
        } else {
            printf("Incorrect. The correct answer is: %s\n", correct_answer);
        }
    }

    printf("\nYou answered %d out of %d questions correctly in the '%s' category.\n",
           correct_answers, total_questions, category_name);
}
