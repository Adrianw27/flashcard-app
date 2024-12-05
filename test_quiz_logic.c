#include <stdio.h>
#include <string.h>
#include "quiz_logic.h"


char flashcard_questions[3][2][50] = {
    {"What is 2 + 2?", "What is 3 + 3?"},
    {"What is the capital of France?", ""},
    {"", ""} 
};
char flashcard_answers[3][2][50] = {
    {"4", "6"},
    {"Paris", ""},
    {"", ""}
};
int flashcard_counts[3] = {2, 1, 0};


int find_category_index(char *category_name) {
    if (strcmp(category_name, "Math") == 0) {
        return 0;
    } else if (strcmp(category_name, "Geography") == 0) {
        return 1;
    } else if (strcmp(category_name, "EmptyCategory") == 0) {
        return 2;
    }
    return -1;
}


void test_to_lowercase() {
    char input[] = "TeStInG";
    char expected_output[] = "testing";
    char output[50]; 
    
    to_lowercase(input, output);
    if (strcmp(output, expected_output) == 0) {
        printf("PASS: to_lowercase\n");
    } else {
        printf("FAIL: to_lowercase\n");
        printf("Expected: %s, Got: %s\n", expected_output, output);
    }
}


void test_start_quiz_valid_category() {
    printf("\nRunning start_quiz with 'Math' category...\n");
    start_quiz("Math");
}


void test_start_quiz_invalid_category() {
    printf("\nRunning start_quiz with invalid category...\n");
    start_quiz("InvalidCategory");
}


void test_start_quiz_empty_category() {
    printf("\nRunning start_quiz with 'EmptyCategory'...\n");
    start_quiz("EmptyCategory");
}





int main() {
    printf("Running Tests...\n");


    test_to_lowercase();

  
    test_start_quiz_valid_category();       
    test_start_quiz_invalid_category();     
    test_start_quiz_empty_category();       

    
    

    printf("\nAll tests completed.\n");
    return 0;
}
