OS := $(shell uname)
CC = g++ 
CFLAGS = -Wall -Werror -Wextra -std=c++17
FLAGS = -lgtest -ftest-coverage -fprofile-arcs
Sanitize = -fsanitize=address -g
TARGET := frontend
SRC=$(wildcard backend/*.cc)

OBJ=$(patsubst backend/%.cc,backend/%.o, ${SRC})

FILE_TEST=$(wildcard tests/s21_*.c)

all: clean s21_smart_calc_oop.a

ifeq ($(OS),Darwin)
	OPEN_CMD = open
else
	FLAGS += -lm -lrt -lsubunit
	OPEN_CMD = xdg-open
endif

all: clean s21_smart_calc_oop.a test

backend/%.o: backend/%.cc  # Use .cc for C++ files
	$(CC) $(CFLAGS) -c -o $@ $<

s21_smart_calc_oop.a: $(OBJ)
	ar rc $@ $^
	ranlib $@

test: clean s21_smart_calc_oop.a
	$(CC) $(CFLAGS) tests/test.cc s21_smart_calc_oop.a $(FLAGS) -o test
	./test

gcov_report: test
	lcov -t "./test"  -o report.info --no-external --ignore-errors mismatch,format,inconsistent -c -d .
	genhtml -o report report.info --ignore-errors inconsistent
	chmod 644 ./report/index.html
	open report/index.html
	rm -rf *.gcno *gcda *.gco

install: uninstall
	mkdir -p build
	cd frontend/ && qmake && make && make clean && rm -rf Makefile && mv $(TARGET).app ../build
	cp -R build/$(TARGET).app ~/Desktop/$(TARGET).app

uninstall:
	rm -rf build/$(TARGET).app
	rm -rf ~/Desktop/$(TARGET).app

rebuild: uninstall install

dvi:
	@open ../README_RUS.md

dist: install
	@mkdir -p ../dist
	@cp -R build/$(TARGET).app ../dist
	@cp ../README_RUS.md ../dist && cp ../README.md ../dist
	@cd ../dist && tar cvzf $(TARGET).tgz *
	@cd ../dist && rm -rf $(TARGET).app README.md README_RUS.md

clean:
	rm -f *.o *.gcda *.a *.gcno *.info backend/*.o
	rm -rf coverage test.dSYM
	rm -f test *.out
	rm -rf *.gcno *gcda *.gcov gcov
	rm -rf report report.info
	rm -rf ../dist
	rm -rf build*


clang:
	clang-format --style=Google -i backend/*.cc backend/*.h Controller/*.h frontend/*.cpp frontend/*.h

.PHONY: all, clean, rebuild, gcov_report, s21_smart_calc.a
