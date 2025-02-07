CC = gcc
CFLAGS =-Wall -Werror -Wextra
CAT = cat/s21_cat.c
GREP = grep/s21_grep.c
SAMPLE1 = num
SAMPLE2 = for|while
SAMPLE3 = res.*
SAMPLE4 = (.*)
SAMPLE5 = not a c file
SAMPLE6 = for while
SAMPLE7 = for
SAMPLE8 = num
SAMPLE9 = (\W|^)po[\-]{0,1}\s{0,1}\d{2}[\s-]{0,1}\d{4}(\W|$)

ifeq ($(OS), Linux)
  LIBS=-lcheck -lpthread -lrt -lm
else
  LIBS=-lcheck
endif

all: s21_cat s21_grep s21_cat_test s21_grep_test

s21_cat: $(CAT)
	$(CC) $(CFLAGS) $(CAT) -o cat/s21_cat

s21_grep: $(GREP)
	$(CC) $(CFLAGS) $(GREP) -o grep/s21_grep

s21_cat_test:
	touch 1.txt
	cat/s21_cat -b cat/1.txt >> cat/s21_cat_test.txt
	cat/s21_cat -e cat/1.txt >> cat/s21_cat_test.txt
	cat/s21_cat -n cat/1.txt >> cat/s21_cat_test.txt
	cat/s21_cat -sv cat/1.txt >> cat/s21_cat_test.txt
	cat/s21_cat -t cat/1.txt >> cat/s21_cat_test.txt
	cat/s21_cat -bes cat/1.txt >> cat/s21_cat_test.txt

	touch 
	cat -b cat/1.txt >> cat/cat_test.txt
	cat -e cat/1.txt >> cat/cat_test.txt
	cat -n cat/1.txt >> cat/cat_test.txt
	cat -sv cat/1.txt >> cat/cat_test.txt
	cat -t cat/1.txt >> cat/cat_test.txt
	cat -bes cat/1.txt >> cat/cat_test.txt
	
	diff -s cat/s21_cat_test.txt cat/cat_test.txt
	rm cat/s21_cat_test.txt cat/cat_test.txt

s21_grep_test: 
	sample="num"
	grep/s21_grep sample grep/s21_grep.c >> grep/s21_grep.txt
	grep sample grep/s21_grep.c >> grep/grep.txt

	sample="for|while"
	grep/s21_grep -iv sample grep/s21_grep.c >> grep/s21_grep.txt
	grep -iv sample grep/s21_grep.c >> grep/grep.txt

	sample="res.*"
	grep/s21_grep -v sample grep/s21_grep.c >> grep/s21_grep.txt
	grep -v sample grep/s21_grep.c >> grep/grep.txt

	sample="(.*)"
	grep/s21_grep -c sample grep/s21_grep.c >> grep/s21_grep.txt
	grep -c sample grep/s21_grep.c >> grep/grep.txt

	sample="not a c file"
	grep/s21_grep -l sample grep/s21_grep.c grep/s21_grep.c grep/s21_grep.c >> grep/s21_grep.txt
	grep -l sample grep/s21_grep.c grep/s21_grep.c grep/s21_grep.c >> grep/grep.txt

	sample="for while"
	grep/s21_grep -nh sample grep/s21_grep.c >> grep/s21_grep.txt
	grep -nh sample grep/s21_grep.c >> grep/grep.txt

	sample="for"
	grep/s21_grep -vhs sample grep/s21_grep.c >> grep/s21_grep.txt
	grep -vhs sample grep/s21_grep.c >> grep/grep.txt

	sample="num"
	grep/s21_grep -s sample grep/s21_grep.c >> grep/s21_grep.txt
	grep -s sample grep/s21_grep.c >> grep/grep.txt

	sample="(\W|^)po[#\-]{0,1}\s{0,1}\d{2}[\s-]{0,1}\d{4}(\W|$)"
	grep/s21_grep -e sample grep/s21_grep.c cat/s21_cat.c >> grep/s21_grep.txt
	grep -e sample grep/s21_grep.c cat/s21_cat.c >> grep/grep.txt

	diff -s grep/s21_grep.txt grep/grep.txt
	rm grep/s21_grep.txt grep/grep.txt

linters: 
	python3 ../materials/linters/cpplint.py --extensions=c cat/*.c grep/*.c cat/*.h grep/*.h

cpp:
	cppcheck --enable=all --suppress=missingIncludeSystem  cat/s21_cat.c grep/s21_grep.c

leaks_cat:
	CK_FORK=no leaks --atExit -- cat/s21_cat

leaks_grep:
	CK_FORK=no leaks --atExit -- grep/s21_grep

debug:
	$(CC) $(CFLAGS) -g $(GREP) -o grep/s21_grep

clean:
	rm -rf cat/*test.txt
	rm -rf cat/s21_cat.o
	rm -rf cat/*.out
	rm -rf cat/s21_cat
	
	rm -rf grep/*.txt
	rm -rf grep/s21_grep.o
	rm -rf *.out
	rm -rf grep/s21_grep
