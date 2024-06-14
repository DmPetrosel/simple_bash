CFLAGS=-Wall -Wextra -Werror -c -std=c11

all: s21_grep

s21_grep: s21_grep.o
	gcc -o s21_grep $<

s21_grep.o: s21_grep.c s21_grep.h
	gcc $(CFLAGS) $<

rebuild: clean all

test: ../tests/test_grep.sh
	bash ../tests/test_grep.sh

valgrind: ../tests/test_grep_valgrind.sh
	bash ../tests/test_grep_valgrind.sh


clean:
	rm -rf *.o s21_grep