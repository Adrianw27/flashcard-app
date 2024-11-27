#ifndef STORAGE_H
#define STORAGE_H


#define MAX_CATEGORIES 10              
#define MAX_CATEGORY_NAME_LENGTH 50    
#define MAX_FLASHCARDS_PER_CATEGORY 20 
#define MAX_QUESTION_LENGTH 256        
#define MAX_ANSWER_LENGTH 256        




extern char category_names[MAX_CATEGORIES][MAX_CATEGORY_NAME_LENGTH];

extern int category_count;


extern char flashcard_questions[MAX_CATEGORIES][MAX_FLASHCARDS_PER_CATEGORY][MAX_QUESTION_LENGTH];
extern char flashcard_answers[MAX_CATEGORIES][MAX_FLASHCARDS_PER_CATEGORY][MAX_ANSWER_LENGTH];

extern int flashcard_counts[MAX_CATEGORIES];


int find_category_index(char category_name[]);


int add_category(char category_name[]);


int add_flashcard(char category_name[], char question[], char answer[]);


void initialize_storage();


void free_storage();

#endif 
