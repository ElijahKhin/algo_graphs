NAME = s21_graph_algorithms.a

PREREQUISITE_GRAPH_ALGO = ../Containers/containers.a \
						  ../Graph/s21_graph.a \
						  Makefile

PREREQUISITE_CONT = ../Containers/Makefile \
					../Containers/Container.h \
					../Containers/ContainerList.h \
					../Containers/Stack.h \
					../Containers/Queue.h \
					../Containers/Container.cc \
					../Containers/ContainerList.cc \
					../Containers/Stack.cc \
					../Containers/Queue.cc


PREREQUISITE_GRAPH = ../Graph/Makefile \
					 ../Graph/s21_graph.cc \
					 ../Graph/s21_graph.h \
					 ../Graph/messages.h

SRC = s21_graph_algorithms.cc
HEADER = s21_graph_algorithms.h messages_algo.h s21_structs.h
TEST = test_graph_algo.cc

OBJ_FOLDER = obj
OBJ = $(SRC:%.cc=$(OBJ_FOLDER)/%.o)

CLR = g++
FLAGS = -std=c++17 -Werror -Wextra -Wall -I.

GCOV_REPORT_NAME = gcov_report

GREEN = \033[32m
YELLOW = \033[0;33m
RED = \033[0;31m
GRAY = \033[2;37m
CURSIVE = \033[3m
NO_COLOR = \x1b[0m


all: $(NAME)
.PHONY: all

$(NAME): $(OBJ_FOLDER) $(OBJ)
	@ar rc $(NAME) obj/*
	@ranlib $(NAME)
	@printf "$(CURSIVE)Wait...⌛ $(YELLOW)%s$(NO_COLOR) successfully assembled! %-37s" $(NAME)""
	@echo "\n"

main:
	@g++ -std=c++17 main.cc -L. $(NAME) ../Containers/containers.a ../Graph/s21_graph.a && ./a.out
$(OBJ_FOLDER):
	@mkdir $(OBJ_FOLDER)

$(OBJ_FOLDER)/%.o: %.cc $(HEADER) $(PREREQUISITE_GRAPH_ALGO)
	@$(CLR) -c $(FLAGS) $< -o $@
	@printf "$(CURSIVE)Compiling source files 🚀... $(YELLOW)%-13s $(NO_COLOR)---> %17.33s ✅\r" $< $@

../Containers/containers.a: $(PREREQUISITE_CONT)
	@make -C ../Containers/

../Graph/s21_graph.a: $(PREREQUISITE_GRAPH)
	@make -C ../Graph/

clean:
	@rm -rf obj
	@rm -rf ./testFiles/*
.PHONY: clean

clean_gcov:
	@rm -rf $(GCOV_REPORT_NAME) $(GCOV_REPORT_NAME).info *.gcda *.gcno report
.PHONY: clean_gcov

fclean: clean clean_gcov
	@rm -rf *.a a.out .*.swp *.*.gch .DS_Store test_bin a.out.dSYM $(NAME)
	@echo "$(GRAY)$(CURSIVE)---$(NAME) staff is completely cleaned!\n"
.PHONY: fclean

re: fclean all
.PHONY: re

test: all
	@g++ -std=c++17 $(TEST) -L. $(NAME) ../Containers/containers.a ../Graph/s21_graph.a -lgtest -lgtest_main -pthread -o test_bin
.PHONY: test

leaks: test
	@leaks --atExit -- ./test_bin
.PHONY: leaks

correct_format:
	@clang-format -i $(SRC) $(TEST) $(HEADER)
.PHONY: correct_format

check_format:
	@clang-format --dry-run --Werror $(SRC) $(TEST) $(HEADER)
.PHONY: check_format
	
report/index.html: $(NAME)
	@g++ -std=c++17 -lgtest --coverage $(TEST) $(SRC) -L. $(NAME) ../Containers/containers.a ../Graph/s21_graph.a -o $(GCOV_REPORT_NAME)
	@./$(GCOV_REPORT_NAME)
	@lcov --no-external --no-recursion -c --directory . -o $(GCOV_REPORT_NAME).info
	@genhtml -o report $(GCOV_REPORT_NAME).info

open_gcov_report: report/index.html $(TEST)
	@open report/index.html
.PHONY: open_gcov_report
