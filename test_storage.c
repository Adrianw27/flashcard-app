#include <stdio.h>
#include <string.h>
#include "storage.h"


void test_find_category_index() {
    printf("\nRunning test for find_category_index...\n");

    initialize_storage();

    add_category("Math");
    add_category("Science");


    if (find_category_index("Math") == 0 && find_category_index("Science") == 1) {
        printf("PASS: find_category_index\n");
    } else {
        printf("FAIL: find_category_index\n");
    }

  
    if (find_category_index("InvalidCategory") == -1) {
        printf("PASS: find_category_index (invalid case)\n");
    } else {
        printf("FAIL: find_category_index (invalid case)\n");
    }

    category_count = -1;
    if (find_category_index("Math") != -1) {
        printf("FAIL: find_category_index (manipulated failure)\n");
    } else {
        printf("PASS: find_category_index (manipulated failure)\n");
    }
    category_count = 0; 
}


void test_add_category() {
    printf("\nRunning test for add_category...\n");

    initialize_storage();

   
    if (add_category("Math") == 1) {
        printf("PASS: add_category (new category)\n");
    } else {
        printf("FAIL: add_category (new category)\n");
    }

  
    if (add_category("Math") == 0) {
        printf("PASS: add_category (duplicate category)\n");
    } else {
        printf("FAIL: add_category (duplicate category)\n");
    }


    for (int i = 0; i < MAX_CATEGORIES; i++) {
        char name[20];
        sprintf(name, "Category%d", i);
        add_category(name);
    }
    if (add_category("ExtraCategory") == -1) {
        printf("PASS: add_category (max limit)\n");
    } else {
        printf("FAIL: add_category (max limit)\n");
    }

    
    category_count = MAX_CATEGORIES + 1;
    if (add_category("OverflowCategory") != -1) {
        printf("FAIL: add_category (manipulated failure)\n");
    } else {
        printf("PASS: add_category (manipulated failure)\n");
    }
    category_count = 0; 
}


void test_add_flashcard() {
    printf("\nRunning test for add_flashcard...\n");

    initialize_storage();
    add_category("Math");


    if (add_flashcard("Math", "What is 2+2?", "4") == 1) {
        printf("PASS: add_flashcard (valid)\n");
    } else {
        printf("FAIL: add_flashcard (valid)\n");
    }

  
    if (add_flashcard("InvalidCategory", "Question?", "Answer") == 0) {
        printf("PASS: add_flashcard (invalid category)\n");
    } else {
        printf("FAIL: add_flashcard (invalid category)\n");
    }

    
    for (int i = 0; i < MAX_FLASHCARDS_PER_CATEGORY; i++) {
        char question[50], answer[50];
        sprintf(question, "Question %d", i);
        sprintf(answer, "Answer %d", i);
        add_flashcard("Math", question, answer);
    }
    if (add_flashcard("Math", "Extra Question?", "Extra Answer") == -1) {
        printf("PASS: add_flashcard (max limit)\n");
    } else {
        printf("FAIL: add_flashcard (max limit)\n");
    }

    
    flashcard_counts[0] = MAX_FLASHCARDS_PER_CATEGORY + 1;
    if (add_flashcard("Math", "Overflow Question", "Overflow Answer") != -1) {
        printf("FAIL: add_flashcard (manipulated failure)\n");
    } else {
        printf("PASS: add_flashcard (manipulated failure)\n");
    }
    flashcard_counts[0] = 0;
}


void test_initialize_storage() {
    printf("\nRunning test for initialize_storage...\n");

    add_category("Math");
    add_flashcard("Math", "What is 2+2?", "4");

    initialize_storage();

   
    if (category_count == 0 && flashcard_counts[0] == 0) {
        printf("PASS: initialize_storage\n");
    } else {
        printf("FAIL: initialize_storage\n");
    }


    initialize_storage();
    if (category_count == 0 && flashcard_counts[0] == 0) {
        printf("PASS: initialize_storage (re-init)\n");
    } else {
        printf("FAIL: initialize_storage (re-init)\n");
    }
}


int main() {
    printf("Running Storage Tests...\n");

    test_find_category_index();
    test_add_category();
    test_add_flashcard();
    test_initialize_storage();

    printf("\nAll tests completed.\n");
    return 0;
}
