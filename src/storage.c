#include "storage.h"
#include <string.h> // For string functions

/*
 * Storage Implementation
 * 
 * This file manages the storage for categories and flashcards, including:
 * - Adding new categories and flashcards
 * - Searching for categories
 * - Initializing and cleaning up storage
 */

// Arrays for storing category names, flashcards, and their counts
char category_names[MAX_CATEGORIES][MAX_CATEGORY_NAME_LENGTH];
char flashcard_questions[MAX_CATEGORIES][MAX_FLASHCARDS_PER_CATEGORY][MAX_QUESTION_LENGTH];
char flashcard_answers[MAX_CATEGORIES][MAX_FLASHCARDS_PER_CATEGORY][MAX_ANSWER_LENGTH];
int flashcard_counts[MAX_CATEGORIES]; // Number of flashcards per category

int category_count = 0; // Total number of categories

/*
 * Function: find_category_index
 *
 * Finds the index of a category by its name.
 *
 * Parameters:
 * - category_name: The name of the category to search for.
 *
 * Returns:
 * - Index of the category (0-based) if found.
 * - -1 if the category does not exist.
 */
int find_category_index(char category_name[]) {
    int i;
    for (i = 0; i < category_count; i++) {
        if (strcmp(category_names[i], category_name) == 0) {
            return i; // Category found
        }
    }
    return -1; // Category not found
}

/*
 * Function: add_category
 * 
 * Adds a new category to the storage.
 *
 * Parameters:
 * - category_name: The name of the category to add.
 *
 * Returns:
 * - 1 if the category was successfully added.
 * - 0 if the category already exists.
 * - -1 if the maximum number of categories has been reached.
 */
int add_category(char category_name[]) {
    if (category_count >= MAX_CATEGORIES) {
        return -1; // Maximum categories reached
    }

    if (find_category_index(category_name) != -1) {
        return 0; // Category already exists
    }

    // Add the category
    strcpy(category_names[category_count], category_name);
    flashcard_counts[category_count] = 0; // Initialize flashcard count for this category
    category_count++; // Increment the category count
    return 1; // Successfully added
}

/*
 * Function: add_flashcard
 *
 * Adds a flashcard to a specific category.
 *
 * Parameters:
 * - category_name: The name of the category to which the flashcard will be added.
 * - question: The question for the flashcard.
 * - answer: The answer for the flashcard.
 *
 * Returns:
 * - 1 if the flashcard was successfully added.
 * - 0 if the category does not exist.
 * - -1 if the maximum number of flashcards for the category has been reached.
 */
int add_flashcard(char category_name[], char question[], char answer[]) {
    int category_index = find_category_index(category_name);
    if (category_index == -1) {
        return 0; // Category does not exist
    }

    if (flashcard_counts[category_index] >= MAX_FLASHCARDS_PER_CATEGORY) {
        return -1; // Maximum flashcards reached for the category
    }

    // Add the flashcard
    int flashcard_index = flashcard_counts[category_index];
    strcpy(flashcard_questions[category_index][flashcard_index], question);
    strcpy(flashcard_answers[category_index][flashcard_index], answer);
    flashcard_counts[category_index]++; // Increment flashcard count for the category
    return 1; // Successfully added
}

/*
 * Function: initialize_storage
 * 
 * Initializes the storage by resetting the category count and flashcard counts.
 *
 * Parameters: None
 * Returns: None
 */
void initialize_storage() {
    category_count = 0;
    int i;
    for (i = 0; i < MAX_CATEGORIES; i++) {
        flashcard_counts[i] = 0; // Reset flashcard counts for all categories
    }
}

/*
 * Function: free_storage
 * 
 * Frees any dynamically allocated memory for storage. 
 * (Currently not used as all storage is static.)
 *
 * Parameters: None
 * Returns: None
 */
void free_storage() {
    // Placeholder for freeing dynamically allocated memory if needed in the future
}
