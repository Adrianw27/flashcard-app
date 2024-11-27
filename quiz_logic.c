#include "quiz_logic.h"
#include "storage.h"
#include <stdio.h>   
#include <string.h>  
#include <ctype.h>  
#include <stdlib.h> 
#include <time.h>    


void to_lowercase(char input[], char output[]) {
    int i = 0;
    while (input[i] != '\0') {
        
        output[i] = tolower((unsigned char)input[i]);
        i++;
    }
    output[i] = '\0'; 
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

    
    srand(time(NULL));

    
    int flashcard_index = rand() % flashcard_counts[category_index];
    char question[MAX_QUESTION_LENGTH];
    char correct_answer[MAX_ANSWER_LENGTH];

    
    strcpy(question, flashcard_questions[category_index][flashcard_index]);
    strcpy(correct_answer, flashcard_answers[category_index][flashcard_index]);

    
    printf("\nQuestion: %s\n", question);


    char user_answer[MAX_ANSWER_LENGTH];
    printf("Your Answer: ");
    if (fgets(user_answer, MAX_ANSWER_LENGTH, stdin) == NULL) {
        printf("Error reading input.\n");
        return;
    }
    
    user_answer[strcspn(user_answer, "\n")] = '\0';

    
    char user_answer_lower[MAX_ANSWER_LENGTH];
    char correct_answer_lower[MAX_ANSWER_LENGTH];
    to_lowercase(user_answer, user_answer_lower);
    to_lowercase(correct_answer, correct_answer_lower);

    
    if (strcmp(user_answer_lower, correct_answer_lower) == 0) {
        printf("Correct!\n");
    } else {
        printf("Incorrect. The correct answer is: %s\n", correct_answer);
    }
}
