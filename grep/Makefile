CC=gcc
FLAGS=-std=c11 -Wall -Werror -Wextra

all: s21_grep
	

s21_grep:
	$(CC) $(FLAGS) s21_grep.c -o s21_grep


test: test_grep 

test_grep: clean_grep
	$(CC) $(FLAGS) s21_grep.c -o s21_grep
	mkdir sasha
# ./s21_grep -s argc s2_grep.c > sasha/grep1 && grep -s argc s2_grep.c > sasha/grep2 && diff sasha/grep1 sasha/grep2
	./s21_grep -e argc s21_grep.c > sasha/grep3 && grep -e argc s21_grep.c > sasha/grep4 && diff sasha/grep3 sasha/grep4
	./s21_grep -n argc s21_grep.c > sasha/grep5 && grep -n argc s21_grep.c > sasha/grep6 && diff sasha/grep5 sasha/grep6
	./s21_grep -i argc s21_grep.c > sasha/grep7 && grep -i argc s21_grep.c > sasha/grep8 && diff sasha/grep7 sasha/grep8
	./s21_grep -c argc s21_grep.c > sasha/grep9 && grep -c argc s21_grep.c > sasha/grep10 && diff sasha/grep9 sasha/grep10
	./s21_grep -v argc s21_grep.c > sasha/grep11 && grep -v argc s21_grep.c > sasha/grep12 && diff sasha/grep11 sasha/grep12
	./s21_grep -l argc s21_grep.c s21_grep.h > sasha/grep13 && grep -l argc s21_grep.c s21_grep.h > sasha/grep14 && diff sasha/grep13 sasha/grep14
	./s21_grep -h argc s21_grep.c s21_grep.h > sasha/grep15 && grep -h argc s21_grep.c s21_grep.h > sasha/grep16 && diff sasha/grep15 sasha/grep16
# ./s21_grep -f s21_grep.c s21_grep.h > sasha/grep17 && grep -f s21_grep.c s21_grep.h > sasha/grep18 && diff sasha/grep17 sasha/grep18
	./s21_grep -o argc s21_grep.c > sasha/grep19 && grep -o argc s21_grep.c > sasha/grep20 && diff sasha/grep19 sasha/grep20

clean: clean_grep

clean_grep:
	rm -rf sasha *.o s21_grep