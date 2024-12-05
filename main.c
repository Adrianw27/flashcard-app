// main.c

/*
 * Flashcard Application
 * ---------------------
 * This is the main entry point for the Flashcard App, which allows users to:
 * - Add categories
 * - Add flashcards to existing categories
 * - Start quizzes based on categories
 * - Display help information
 *
 * Dependencies:
 * - GTK 4.0
 * - storage.h (Handles storage and category management)
 * - quiz_logic.h (Implements quiz logic)
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gtk/gtk.h>  // GTK 4.0
#include "storage.h"
#include "quiz_logic.h"

/*
 * Function: display_help
 * ----------------------
 * Displays a help message detailing the usage of the Flashcard App.
 *
 * Parameters: None
 * Returns: None
 */
void display_help() {
    printf("Flashcard App Help\n");
    printf("------------------\n");
    printf("Usage:\n");
    printf("  ./flashcardapp [--help]\n");
    printf("\n");
    printf("Options:\n");
    printf("  --help    Display this help message and exit.\n");
    printf("\n");
    printf("Interactive Menu Options:\n");
    printf("  1. Add Category    - Add a new category.\n");
    printf("  2. Add Flashcard   - Add a flashcard to an existing category.\n");
    printf("  3. Start Quiz      - Start a quiz for a category.\n");
    printf("  4. Exit            - Exit the application.\n");
    printf("\n");
    printf("Note: The application does not save data between sessions.\n");
}

/*
 * Function: display_menu
 * ----------------------
 * Displays the interactive menu for the Flashcard App.
 *
 * Parameters: None
 * Returns: None
 */
void display_menu() {
    printf("\nFlashcard App Menu:\n");
    printf("1. Add Category\n");
    printf("2. Add Flashcard\n");
    printf("3. Start Quiz\n");
    printf("4. Exit\n");
    printf("Enter your choice (1-4): ");
}

/*
 * Function: main
 * --------------
 * Main function that initializes the application, handles user input, and
 * manages the interactive menu for the Flashcard App.
 *
 * Parameters:
 * - argc: Argument count
 * - argv: Argument vector (list of command-line arguments)
 *
 * Returns:
 * - 0 on successful execution
 */
int main(int argc, char *argv[]) {
    if (argc > 1 && strcmp(argv[1], "--help") == 0) {
        display_help();
        return 0;
    }

    // Initialize GTK
    gtk_init();

    int choice;
    char input_buffer[256];

    // Initialize storage for categories and flashcards
    initialize_storage();

    while (1) {
        display_menu();
        if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
            printf("Error reading input. Exiting.\n");
            break;
        }
        choice = atoi(input_buffer);

        if (choice == 1) {
            // Add Category
            char category_name[MAX_CATEGORY_NAME_LENGTH];
            printf("Enter the category name: ");
            if (fgets(category_name, MAX_CATEGORY_NAME_LENGTH, stdin) == NULL) {
                printf("Error reading input.\n");
                continue;
            }
            category_name[strcspn(category_name, "\n")] = '\0';
            int result = add_category(category_name);
            if (result == 1) {
                printf("Category '%s' added successfully.\n", category_name);
            } else if (result == 0) {
                printf("Category '%s' already exists.\n", category_name);
            } else {
                printf("Maximum number of categories reached.\n");
            }
        } else if (choice == 2) {
            // Add Flashcard
            char category_name[MAX_CATEGORY_NAME_LENGTH];
            char question[MAX_QUESTION_LENGTH];
            char answer[MAX_ANSWER_LENGTH];

            printf("Enter the category name: ");
            if (fgets(category_name, MAX_CATEGORY_NAME_LENGTH, stdin) == NULL) {
                printf("Error reading input.\n");
                continue;
            }
            category_name[strcspn(category_name, "\n")] = '\0';

            printf("Enter the question: ");
            if (fgets(question, MAX_QUESTION_LENGTH, stdin) == NULL) {
                printf("Error reading input.\n");
                continue;
            }
            question[strcspn(question, "\n")] = '\0';

            printf("Enter the answer: ");
            if (fgets(answer, MAX_ANSWER_LENGTH, stdin) == NULL) {
                printf("Error reading input.\n");
                continue;
            }
            answer[strcspn(answer, "\n")] = '\0';

            int result = add_flashcard(category_name, question, answer);
            if (result == 1) {
                printf("Flashcard added to category '%s' successfully.\n", category_name);
            } else if (result == 0) {
                printf("Category '%s' does not exist.\n", category_name);
            } else {
                printf("Maximum number of flashcards reached for category '%s'.\n", category_name);
            }
        } else if (choice == 3) {
            // Start Quiz
            char category_name[MAX_CATEGORY_NAME_LENGTH];
            printf("Enter the category name to start the quiz: ");
            if (fgets(category_name, MAX_CATEGORY_NAME_LENGTH, stdin) == NULL) {
                printf("Error reading input.\n");
                continue;
            }
            category_name[strcspn(category_name, "\n")] = '\0';
            start_quiz(category_name);
        } else if (choice == 4) {
            // Exit
            printf("Exiting the Flashcard App. Goodbye!\n");
            break;
        } else {
            // Invalid Input
            printf("Invalid choice. Please enter a number between 1 and 4.\n");
        }
    }

    // Free resources allocated for storage
    free_storage();
    return 0;
}
