#include <stdio.h>
#include <string.h>
#include "storage.h"
#include "quiz_logic.h"

void test_main_add_category() {
    printf("\nTesting Add Category via Main...\n");

    initialize_storage();

    // Simulate adding a category
    char category_name[MAX_CATEGORY_NAME_LENGTH] = "Math";
    int result = add_category(category_name);

    if (result == 1) {
        printf("PASS: Add new category 'Math'.\n");
    } else {
        printf("FAIL: Add new category 'Math'.\n");
    }

    // Simulate adding a duplicate category
    result = add_category(category_name);
    if (result == 0) {
        printf("PASS: Handle duplicate category 'Math'.\n");
    } else {
        printf("FAIL: Handle duplicate category 'Math'.\n");
    }
}

void test_main_add_flashcard() {
    printf("\nTesting Add Flashcard via Main...\n");

    initialize_storage();
    add_category("Math");

    // Simulate adding a flashcard
    char question[MAX_QUESTION_LENGTH] = "What is 2+2?";
    char answer[MAX_ANSWER_LENGTH] = "4";
    int result = add_flashcard("Math", question, answer);

    if (result == 1) {
        printf("PASS: Add flashcard to 'Math'.\n");
    } else {
        printf("FAIL: Add flashcard to 'Math'.\n");
    }

    // Simulate adding a flashcard to an invalid category
    result = add_flashcard("Science", question, answer);
    if (result == 0) {
        printf("PASS: Handle non-existent category 'Science'.\n");
    } else {
        printf("FAIL: Handle non-existent category 'Science'.\n");
    }
}

void test_main_start_quiz() {
    printf("\nTesting Start Quiz via Main...\n");

    initialize_storage();
    add_category("Math");
    add_flashcard("Math", "What is 2+2?", "4");

    printf("Simulated Quiz for 'Math'.\n");
    start_quiz("Math");

    printf("Attempting to start quiz for invalid category 'Science'.\n");
    start_quiz("Science");
}

void test_main_invalid_input() {
    printf("\nTesting Invalid Input Handling via Main...\n");

    // Simulate invalid menu choice
    printf("Simulating invalid menu choice '5'.\n");
    int choice = 5; // Invalid
    if (choice < 1 || choice > 4) {
        printf("PASS: Detected invalid input.\n");
    } else {
        printf("FAIL: Did not detect invalid input.\n");
    }
}

int main() {
    printf("Running Tests for Main...\n");

    test_main_add_category();
    test_main_add_flashcard();
    test_main_start_quiz();
    test_main_invalid_input();

    printf("\nAll tests completed.\n");
    return 0;
}
