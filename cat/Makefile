CFLAGS=-Wall -Wextra -Werror -c -std=c11

all: s21_cat

s21_cat: s21_cat.o 
	gcc -o s21_cat $<


s21_cat.o: s21_cat.c s21_cat.h
	gcc $(CFLAGS) $<

rebuild: clean all

test: ../tests/test_cat.sh
	bash ../tests/test_cat.sh

valgrind: ../tests/test_cat_valgrind.sh
	bash ../tests/test_cat_valgrind.sh

clean:
	rm -rf *.o s21_cat