// quiz_logic.c

#include "quiz_logic.h"
#include "storage.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <gtk/gtk.h>   
#include <glib.h>      




void to_lowercase(char input[], char output[]) {
    int i = 0;
    while (input[i] != '\0') {
        output[i] = tolower((unsigned char)input[i]);
        i++;
    }
    output[i] = '\0'; 
}






void on_activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *image;

 
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Correct Answer!");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);


    image = gtk_image_new_from_file("happy.png");


    if (image == NULL) {
        g_printerr("Error: Unable to load image 'happy.png'.\n");
        g_application_quit(G_APPLICATION(app));
        return;
    }

  
    gtk_window_set_child(GTK_WINDOW(window), image);

    gtk_window_present(GTK_WINDOW(window));
}

void show_happy_image() {
    
    GtkApplication *app = gtk_application_new("com.example.GtkApp", G_APPLICATION_FLAGS_NONE);

   
    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);

 
    g_application_run(G_APPLICATION(app), 0, NULL);

  
    g_object_unref(app);
}




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

        char user_answer_lower[MAX_ANSWER_LENGTH];
        char correct_answer_lower[MAX_ANSWER_LENGTH];
        to_lowercase(user_answer, user_answer_lower);
        to_lowercase(correct_answer, correct_answer_lower);

        if (strcmp(user_answer_lower, correct_answer_lower) == 0) {
            printf("Correct!\n");
            correct_answers++;

           
            show_happy_image();
        } else {
            printf("Incorrect. The correct answer is: %s\n", correct_answer);
            
        }
    }

    printf("\nYou answered %d out of %d questions correctly in the '%s' category.\n",
           correct_answers, total_questions, category_name);
}
