#include "storage.h"
#include <string.h> // For string functions




char category_names[MAX_CATEGORIES][MAX_CATEGORY_NAME_LENGTH];

int category_count = 0;


char flashcard_questions[MAX_CATEGORIES][MAX_FLASHCARDS_PER_CATEGORY][MAX_QUESTION_LENGTH];
char flashcard_answers[MAX_CATEGORIES][MAX_FLASHCARDS_PER_CATEGORY][MAX_ANSWER_LENGTH];

int flashcard_counts[MAX_CATEGORIES];

int find_category_index(char category_name[]) {
    int i;
    for (i = 0; i < category_count; i++) {
        
        if (strcmp(category_names[i], category_name) == 0) {
            return i; 
        }
    }
    return -1; 
}

int add_category(char category_name[]) {
    
    if (category_count >= MAX_CATEGORIES) {
        return -1; 
    }
    
    if (find_category_index(category_name) != -1) {
        return 0; 
    }
    
    strcpy(category_names[category_count], category_name);
    flashcard_counts[category_count] = 0; 
    category_count++; 
    return 1; 
}


int add_flashcard(char category_name[], char question[], char answer[]) {
    int category_index = find_category_index(category_name);
    if (category_index == -1) {
        return 0; 
    }
    
    if (flashcard_counts[category_index] >= MAX_FLASHCARDS_PER_CATEGORY) {
        return -1; 
    }
    int flashcard_index = flashcard_counts[category_index];
    
    strcpy(flashcard_questions[category_index][flashcard_index], question);
    strcpy(flashcard_answers[category_index][flashcard_index], answer);
    flashcard_counts[category_index]++; 
    return 1; 
}

void initialize_storage() {
  
    category_count = 0;
    int i;
    for (i = 0; i < MAX_CATEGORIES; i++) {
        flashcard_counts[i] = 0;
    }
}


void free_storage() {
    
}
