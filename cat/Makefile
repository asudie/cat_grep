CC=gcc
FLAGS=-std=c11 -Wall -Werror -Wextra

all: s21_cat
	

s21_cat:
	$(CC) $(FLAGS) s21_cat.c -o s21_cat


test: test_cat 

test_cat: clean_cat
	$(CC) $(FLAGS) s21_cat.c -o s21_cat
	mkdir sasha
	./s21_cat -s try.txt > sasha/cat1 && cat -s try.txt > sasha/cat2 && diff sasha/cat1 sasha/cat2
	./s21_cat -e try.txt > sasha/cat3 && cat -e try.txt > sasha/cat4 && diff sasha/cat3 sasha/cat4
	./s21_cat -n try.txt > sasha/cat5 && cat -n try.txt > sasha/cat6 && diff sasha/cat5 sasha/cat6
	./s21_cat -b try.txt > sasha/cat7 && cat -b try.txt > sasha/cat8 && diff sasha/cat7 sasha/cat8
	./s21_cat -t try.txt > sasha/cat9 && cat -t try.txt > sasha/cat10 && diff sasha/cat9 sasha/cat10
	./s21_cat -v bytes.txt > sasha/cat11 && cat -v bytes.txt > sasha/cat12 && diff sasha/cat11 sasha/cat12

clean: clean_cat

clean_cat:
	rm -rf sasha *.o s21_cat

