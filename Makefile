CC = gcc

CFLAGS = -Wall -g

SRC = main.c storage.c quiz_logic.c

OBJ = $(SRC:.c=.o)

APP = flashcardapp

all: $(APP)

$(APP): $(OBJ)
	$(CC) $(CFLAGS) -o $(APP) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(APP) *.gcno *.gcda *.gcov coverage.info
	rm -rf coverage

coverage: clean
	$(MAKE) CFLAGS="$(CFLAGS) --coverage" LDFLAGS="--coverage" all

gcov-report:
	mkdir -p coverage
	# Generate gcov files and redirect output to test_results.txt
	for file in $(SRC); do \
		gcov -o . $$file >> test_results.txt; \
	done
	# Move gcov files to coverage directory
	mv *.gcov coverage/

html-report:
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory coverage
