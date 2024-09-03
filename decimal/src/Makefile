# Компилятор
CC = gcc
# Стандартные флаги
FLAGS = -Wall -Werror -Wextra -std=c11 
# Флаги покрытия для генерации html отчета
-FLAGS_COV = -fprofile-arcs -ftest-coverage
# Файлы .check с тестами для преобразования в исходные файлы C с тестами
CH_FILES = $(wildcard ./tests/*.check)
# Все файлы исходники .c
C_FILES = $(wildcard ./common_helpers/*.c) $(wildcard ./arithmetic_operations/*.c) $(wildcard ./convertors_and_parsers/*.c) $(wildcard ./other_functions/*.c) $(wildcard ./comparison_operators/*.c) $(wildcard ./big_dec/*.c)

# Если операционная система Linux
ifeq ($(shell uname -s), Linux)
	OC = Linux
    # Флаги для использования утилиты checkmk на Linux -f отчет по функциям
	FLAGS_CHECK = -lcheck -lm -lpthread -pthread -lsubunit -lgcov
	ifeq ($(shell which xdg-open),)
    	OPEN = w3m report/index-sort-f.html
	else
    	OPEN = xdg-open report/index-sort-f.html
	endif
# Если операционная система macOS
else ifeq ($(shell uname -s), Darwin)
	OC = Darwin
    # Флаги для использования утилиты checkmk на macOS -f отчет по функциям
    FLAGS_CHECK = -lcheck -lm -lpthread -pthread
	OPEN = open report/index-sort-f.html
endif

# Инициализируем цели работы - все цели работы test gcov_report
all: s21_decimal.a 

# Создаем статическую библиотеку .a для вертера
s21_decimal.a: s21_decimal.o
	ar rc s21_decimal.a *.o

# Компилируем исходные файлы для создания библиотеки для вертера
s21_decimal.o: $(C_FILES)
	$(CC) $(FLAGS) -c $^

# Компилируем объектные файлы с покрытием для приров
coverege_o: $(C_FILES)
	$(CC) $(FLAGS) --coverage -c $^

# Компилируем библиотеку с покрытием для пиров
coverage_a: coverege_o
	ar rc s21_decimal.a *.o

# Компилируем тесты с помощью checkmk и запускаем
# Чистим исполняемые файлы
test: clean $(CH_FILES) coverage_a
	for file in $(CH_FILES); do \
		checkmk clean_mode=1 $$file > $${file%.*}.c; \
		$(CC) $(FLAGS) --coverage $${file%.*}.c s21_decimal.a -o $${file%.*}.exe $(FLAGS_CHECK); \
		./$${file%.*}.exe && echo "\n"; \
		rm $${file%.*}.exe; \
	done

# Проверка на утечки - прям по инструкции из ридмихи
leak: clean $(CH_FILES) s21_decimal.a
	checkmk clean_mode=1 $(CH_FILES) >> ./tests/main.c
	$(CC) $(FLAGS) ./tests/main.c s21_decimal.a -o ./tests/main.out $(FLAGS_CHECK)

# На маке leaks чет не работает как надо
# В докере vailgrind работает на убунте хорошо
ifeq ($(OC), Darwin)
	leaks -atExit -- ./tests/main.out | grep LEAK:
else ifeq ($(OC), Linux)
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes ./tests/main.out
endif

# Отчет о покрытии кода
gcov_report: test
	lcov -t "s21_decimal" -o s21_decimal.info -c -d . 
	genhtml -o ./report s21_decimal.info
	$(OPEN)

# Пересборка
rebuild: clean gcov_report

#clang format - чтобы убедиться что все отформатированно
clang:
	mv ../materials/linters/.clang-format ./
	find . -name "*.c" -exec clang-format -n {} \;
	find . -name "*.h" -exec clang-format -n {} \;
	mv .clang-format ../materials/linters/

#Чистим трубы
clean:
	rm -rf *.o *.a *.gcda *.gcno *.html *.css *.info tests/*.exe tests/*.c tests/*.out *.gcd s21_decimal.h.gch s21_decimal report
	find . -type f -name '*.gcda' -delete
	find . -type f -name '*.gcno' -delete
	clear
