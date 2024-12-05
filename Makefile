flashcardapp: quiz_logic.c quiz_logic.h storage.c storage.h main.c
	gcc quiz_logic.c quiz_logic.h storage.c storage.h main.c -o flashcardapp `pkg-config --cflags --libs gtk4`